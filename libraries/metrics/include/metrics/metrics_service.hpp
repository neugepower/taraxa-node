#pragma once

#include <functional>
#include <string>

namespace taraxa::metrics {

void setNetworkPeersCounterCallback(std::function<int64_t()> const& callback);

/**
 * @brief class for metrics collecting. Registering specific metrics classes and creating prometheus server(exposer)
 */
class MetricsService {

 public:
  explicit MetricsService(const std::string& host, uint16_t port, uint16_t polling_interval_ms)
  : host_(host)
  , port_(port)
  , polling_interval_ms_(polling_interval_ms) {}
  ~MetricsService();

  /**
   * @brief method to start thread that collecting data from special classes
   */
  void start();

 private:
  const std::string host_;
  const uint16_t port_;
  const uint16_t polling_interval_ms_ = 0;
};
}  // namespace taraxa::metrics
