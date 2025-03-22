#include "metrics/metrics_service.hpp"

//#include <prometheus/counter.h>

#include <iostream>
#include <memory>
#include <thread>

namespace taraxa::metrics {
namespace {
  std::function<int64_t()> callback_;

  int64_t getValue() {
    return callback_();
  }
}


typedef int64_t (*Callback)();

#ifdef __cplusplus
extern "C" {
start_metric_service();
stop_metric_service();

void register_network_peers_counter_callback(Callback callback);
void register_network_discovered_peers_counter_callback(Callback callback);
#endif
#ifdef __cplusplus
}
#endif


void setNetworkPeersCounterCallback(std::function<int64_t()> const& callback) {
  callback_ = callback;
  register_network_peers_counter_callback(&getValue);
}

// ---

MetricsService::~MetricsService() {
  // stop_metric_service()
}

void MetricsService::start() {
  create_metric_service();
}



}  // namespace taraxa::metrics
