#pragma once

#include "metrics/metrics_service.hpp"
#include "metrics/network_metrics.hpp"

namespace taraxa::metrics {

class MetricsManager {
 public:
  static MetricsManager& instance() {
    static MetricsManager instance;
    return instance;
  }

  void setMetricsService(MetricsService& metrics_service) { metrics_ = &metrics_service; }

  template <class T>
  T& getMetrics() {
    return *metrics_->getMetrics<T>().get();
  }

  void registerCounters() { metrics_->getMetrics<metrics::NetworkMetrics>()->registerCounters(); }

 private:
  MetricsService* metrics_;
};
}  // namespace taraxa::metrics
