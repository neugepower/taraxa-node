#pragma once

#include <prometheus/counter.h>
#include <prometheus/gauge.h>
#include <prometheus/histogram.h>
#include <prometheus/registry.h>

#include <array>

namespace taraxa::metrics {

/**
 * @brief add method that is setting specific gauge metric.
 */
#define ADD_GAUGE_METRIC(method, name, description)                                                  \
  void method(double v) {                                                                            \
    static auto& label = addMetric<prometheus::Gauge>(group_name + "_" + name, description).Add({}); \
    label.Set(v);                                                                                    \
  }

/**
 * @brief add method that is setting specific counter metric.
 */
#define ADD_COUNTER_METRIC(method, name, description)                                                  \
  void method(double v) {                                                                              \
    static auto& label = addMetric<prometheus::Counter>(group_name + "_" + name, description).Add({}); \
    label.Increment(v);                                                                                \
  }

/**
 * @brief add method that is setting specific histogram metric.
 */
#define ADD_HISTOGRAM_METRIC(method, name, description, buckets)                                           \
  void method(double v, std::map<std::string, std::string> labels) {                                       \
    static auto& label = addMetric<prometheus::Histogram>(group_name + "_" + name, description);           \
    label.Add(labels, prometheus::Histogram::BucketBoundaries{buckets.begin(), buckets.end()}).Observe(v); \
  }

/**
 * @brief add updater method.
 * This is used to store lambda function that updates metric, so we can update it periodically
 * Passed `method` should be added first
 */
#define ADD_UPDATER_METHOD(method)                               \
  void method##Updater(MetricGetter getter) {                    \
    updaters_.push_back([this, getter]() { method(getter()); }); \
  }

/**
 * @brief combines ADD_UPDATER_METHOD and ADD_GAUGE_METRIC
 */
#define ADD_GAUGE_METRIC_WITH_UPDATER(method, name, description) \
  ADD_GAUGE_METRIC(method, name, description)                    \
  ADD_UPDATER_METHOD(method)

/**
 * @brief combines ADD_UPDATER_METHOD and ADD_COUNTER_METRIC
 */
#define ADD_COUNTER_METRIC_WITH_UPDATER(method, name, description) \
  ADD_COUNTER_METRIC(method, name, description)                    \
  ADD_UPDATER_METHOD(method)

/**
 * @brief Extracts enum, name, or description from AllCounters in ADD_COUNTERS macro.
 */
#define COUNTERS_ENUM(Enum, Name, Description) Enum,
#define COUNTERS_NAME(Enum, Name, Description) Name,
#define COUNTERS_DESCRIPTION(Enum, Name, Description) Description,

/**
 * @brief Adds a set of counters and accessors to a given class.
 *
 * @todo Add a compile assert to make sure that Counter is < AllCounters::Count.
 */
#define ADD_COUNTERS_AND_ACCESSORS(AllCounters)                                                         \
  struct Counters {                                                                                     \
    enum {                                                                                              \
      AllCounters(COUNTERS_ENUM) Count,                                                                 \
    };                                                                                                  \
    static constexpr std::array<const char*, Count> names = {AllCounters(COUNTERS_NAME)};               \
    static constexpr std::array<const char*, Count> descriptions = {AllCounters(COUNTERS_DESCRIPTION)}; \
    std::array<std::atomic<uint64_t>, Count> counters;                                                  \
    std::vector<prometheus::Counter*> labels;                                                           \
  } counters_;                                                                                          \
                                                                                                        \
  template <auto Counter>                                                                               \
  uint64_t incrementCounter() {                                                                         \
    return counters_.counters[static_cast<size_t>(Counter)].fetch_add(1, std::memory_order_relaxed);    \
  }                                                                                                     \
                                                                                                        \
  void registerCounters() {                                                                             \
    for (size_t i = 0; i < counters_.Count; ++i) {                                                      \
      auto& counter = prometheus::detail::Builder<prometheus::Counter>()                                \
                          .Name(counters_.names[i])                                                     \
                          .Help(counters_.descriptions[i])                                              \
                          .Register(*registry_)                                                         \
                          .Add({});                                                                     \
      counters_.labels.push_back(&counter);                                                             \
    }                                                                                                   \
                                                                                                        \
    updaters_.push_back([this]() {                                                                      \
      for (size_t i = 0; i < counters_.Count; ++i) {                                                    \
        counters_.labels[i]->Increment(counters_.counters[i].exchange(0, std::memory_order_relaxed));   \
      }                                                                                                 \
    });                                                                                                 \
  }

class MetricsGroup {
 public:
  using MetricGetter = std::function<double()>;
  using MetricUpdater = std::function<void()>;
  MetricsGroup(std::shared_ptr<prometheus::Registry> registry) : registry_(std::move(registry)) {}
  virtual ~MetricsGroup() = default;

  /**
   * @brief template method to add metric family.
   * Family is a metric, but additional labels could be specified for it. Labels if optional.
   * @tparam Type type of prometheus metric that should be added
   * @param name metric name
   * @param help help string for metric(description)
   * @return Family<T>
   */
  template <class Type>
  prometheus::Family<Type>& addMetric(const std::string& name, const std::string& help) {
    return prometheus::detail::Builder<Type>().Name(name).Help(help).Register(*registry_);
  }
  /**
   * @brief method that is used to call registered updaters for the specific class
   */
  virtual void updateData() {
    for (auto& update : updaters_) {
      update();
    }
  }

 protected:
  std::shared_ptr<prometheus::Registry> registry_;
  std::vector<MetricUpdater> updaters_;
};

class MetricsGroupStub : public MetricsGroup {
 public:
  MetricsGroupStub() : MetricsGroup(nullptr) {}

  void updateData() override {}

  template <auto Counter>
  uint64_t incrementCounter() {
    return 0;
  }
};

using SharedMetricsGroup = std::shared_ptr<MetricsGroup>;
}  // namespace taraxa::metrics
