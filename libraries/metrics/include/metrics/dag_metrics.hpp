#pragma once

#include "metrics/metrics_group.hpp"

namespace taraxa::metrics {
class DagMetrics : public MetricsGroup {
 public:
  inline static const std::string group_name = "dag";
  DagMetrics(std::shared_ptr<prometheus::Registry> registry) : MetricsGroup(std::move(registry)) {}

  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceived, "received_count", "Count of received dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementVerified, "verified_count", "Count of verified dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementMissingTransactions, "missing_transactions_count",
                                  "Count of dag blocks missing transactions")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementAhead, "ahead_block_count", "Count ahead of block dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementFailedVdfVerification, "failed_vdf_verification_count",
                                  "Count dag blocks failed VDF verification")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementFuture, "future_block_count", "Count future dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementNotEligible, "not_eligible_count", "Count dag blocks not eligible")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementExpired, "expired_block_count", "Count expired dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementIncorrectTransactionsEstimation, "incorrect_transactions_estimation_count",
                                  "Count incorrect transactions estimation dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementTooBig, "block_too_big_count", "Count dag blocks too big")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementFailedTipsVerification, "failed_tips_verificaction_count",
                                  "Count dag blocks failed tips verification")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementMissingTip, "missing_tip_count", "Count dag blocks missing tips")
};

}  // namespace taraxa::metrics
