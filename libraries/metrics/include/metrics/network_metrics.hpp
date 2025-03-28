#pragma once

#include "metrics/metrics_group.hpp"

namespace taraxa::metrics {
class NetworkMetrics : public MetricsGroup {
 public:
  inline static const std::string group_name = "network";
  NetworkMetrics(std::shared_ptr<prometheus::Registry> registry) : MetricsGroup(std::move(registry)) {}
  ADD_GAUGE_METRIC_WITH_UPDATER(setPeersCount, "peers_count", "Count of peers that node is connected to")
  ADD_GAUGE_METRIC_WITH_UPDATER(setDiscoveredPeersCount, "discovered_peers_count", "Count of discovered peers")
  ADD_GAUGE_METRIC_WITH_UPDATER(setSyncingDuration, "syncing_duration_sec", "Time node is currently in sync state")

  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedPacketsCount, "received_packets_count",
                                  "Count of received network packets")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedFilteredPacketsCount, "received_filtered_packets_count",
                                  "Count of received filtered network packets")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedTooEarlyPacketsCount, "dropped_too_early_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedSyncingPacketsCount, "dropped_syncing_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPeersProcessingTimeTooHighPacketsCount,
                                  "dropped_peers_processing_time_too_high_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedWrongTarcapVersionPacketsCount,
                                  "dropped_wrong_tarcap_version_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPeerLostPacketsCount, "dropped_peer_lost_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedMaliciousPeerPacketsCount, "dropped_malicious_peer_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedBadPacketsCount, "dropped_bad_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedRlpBadPacketsCount, "dropped_rlp_bad_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedUnknownErrorPacketsCount, "dropped_unknown_error_packets_count", "")

  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceviedPillarVotePacketsCount, "received_pillar_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementProcessedPillarVotePacketsCount, "processed_pillar_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementSendPillarVotePacketsCount, "send_pillar_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPillarIrrelevantVotePacketsCount,
                                  "dropped_pillar_irrelevant_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPillarInvalidVotePacketsCount,
                                  "dropped_pillar_invalid_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPillarOldPeriodVotePacketsCount,
                                  "dropped_pillar_old_period_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedPillarBundleVotePacketsCount,
                                  "received_pillar_bundle_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPillarBundleOldPeriodVotePacketsCount,
                                  "dropped_pillar_bundle_old_period_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPillarBundleTooLargeVotePacketsCount,
                                  "dropped_pillar_bundle_too_large_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedGetPillarBundleVoteCount,
                                  "received_get_pillar_bundle_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedGetPillarBundleOldPeriodVotePacketsCount,
                                  "dropped_get_pillar_bundle_old_period_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedGetPillarBundleWrongPeriodVotePacketsCount,
                                  "dropped_get_pillar_bundle_wrong_period_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedGetPillarBundleEmptyVotePacketsCount,
                                  "dropped_get_pillar_bundle_empty_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementSendPillarBundleVotePacketsCount, "send_pillar_bundle_vote_packets_count",
                                  "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementRequestPillarBundleVotePacketsCount,
                                  "request_pillar_bundle_vote_packets_count", "")

  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedDagPacketsCount, "received_dag_packets_count",
                                  "Count of received dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedKnownDagPacketsCount, "dropped_known_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementSendDagPacketsCount, "sent_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementFailedSendDagPacketsCount, "failed_sent_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementVerifiedDagPacketsCount, "verified_dag_packets_count",
                                  "Count of verified dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedMissingTransactionsDagPacketsCount,
                                  "dropped_missing_transactions_dag_packets_count",
                                  "Count of dag blocks missing transactions")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedAheadDagPacketsCount, "dropped_ahead_block_dag_packets_count",
                                  "Count ahead of block dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedFailedVdfVerificationDagPacketsCount,
                                  "dropped_failed_vdf_verification_count", "Count dag blocks failed VDF verification")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedFutureDagPacketsCount, "dropped_future_block_dag_packets_count",
                                  "Count future dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedNotEligibleDagPacketsCount, "dropped_not_eligible_dag_packets_count",
                                  "Count dag blocks not eligible")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedExpiredDagPacketsCount, "dropped_expired_block_dag_packets_count",
                                  "Count expired dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedIncorrectTransactionsEstimationDagPacketsCount,
                                  "dropped_incorrect_transactions_estimation_dag_packets_count",
                                  "Count incorrect transactions estimation dag blocks")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedTooBigDagPacketsCount, "dropped_block_too_big_dag_packets_count",
                                  "Count dag blocks too big")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedFailedTipsVerificationDagPacketsCount,
                                  "dropped_failed_tips_verificaction_dag_packets_count",
                                  "Count dag blocks failed tips verification")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedMissingTipDagPacketsCount, "dropped_missing_tip_dag_packets_count",
                                  "Count dag blocks missing tips")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementRequestDagPacketsCount, "request_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementRequestSendDagPacketsCount, "request_send_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementRequestFailedNoPeerMatchDagPacketsCount,
                                  "request_failed_no_peer_match_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementRequestFailedNoPeersDagPacketsCount,
                                  "request_failed_no_peers_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementRequestFailedAlreadyRequestedFromPeerDagPacketsCount,
                                  "request_failed_already_requested_from_peer_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementRequestFailedUnmatchedPeriodDagPacketsCount,
                                  "request_failed_unmatched_period_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedSendSyncDagPacketsCount, "dropped_send_sync_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedSendNoPeerDagPacketsCount, "dropped_send_no_peers_dag_packets_count",
                                  "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedSyncDagPacketsCount, "received_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementVerifiedSyncDagPacketsCount, "verified_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedPastPeriodSyncDagPacketsCount,
                                  "dropped_past_period_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedFuturePeriodSyncDagPacketsCount,
                                  "dropped_future_period_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedTxInvalidSyncDagPacketsCount,
                                  "dropped_tx_invalid_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedInvalidVerifySyncDagPacketsCount,
                                  "dropped_invalid_verify_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedInvalidSyncDagPacketsCount,
                                  "dropped_invalid_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedGetSyncDagPacketsCount, "received_get_sync_dag_dag_packets_count",
                                  "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementDroppedNotAllowedGetSyncDagPacketsCount,
                                  "dropped_not_allowed_get_sync_dag_dag_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementSendGetSyncDagPacketsCount, "send_get_sync_dag_dag_packets_count", "")

  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedVotePacketsCount, "received_vote_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedVotesBundlePacketsCount, "received_votes_bundle_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedGetNextVotesPacketsCount, "received_get_next_votes_packets_count",
                                  "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedPbftSyncPacketsCount, "received_pbft_sync_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedGetPbftSyncPacketsCount, "received_get_pbft_sync_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedStatusPacketsCount, "received_status_packets_count", "")
  ADD_COUNTER_METRIC_WITH_UPDATER(incrementReceivedTxPacketsCount, "received_tx_packets_count", "")

  ADD_GAUGE_METRIC_WITH_UPDATER(setPacketQueueLowSize, "packet_queue_low_size", "")
  ADD_GAUGE_METRIC_WITH_UPDATER(setPacketQueueMidSize, "packet_queue_mid_size", "")
  ADD_GAUGE_METRIC_WITH_UPDATER(setPacketQueueHighSize, "packet_queue_high_size", "")
};
}  // namespace taraxa::metrics
