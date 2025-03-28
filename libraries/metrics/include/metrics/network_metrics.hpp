#pragma once

#include "metrics/metrics_group.hpp"

namespace taraxa::metrics {

#define NETWORK_METRICS_COUNTERS(X)                                                                                \
  X(PacketsTotal, "network_packets_total_count", "")                                                               \
  X(PacketsCleared, "network_packets_cleared_count", "")                                                           \
  X(PacketsDroppedEarly, "network_packets_dropped_early_count", "")                                                \
  X(PacketsDroppedSyncing, "network_packets_dropped_syncing_count", "")                                            \
  X(PacketsDroppedProcessingHigh, "network_packets_dropped_processing_high_count", "")                             \
  X(PacketsDroppedWrongTarcap, "network_packets_dropped_wrong_tarcap_count", "")                                   \
  X(PacketsDroppedPeerLost, "network_packets_dropped_peer_lost_count", "")                                         \
  X(PacketsDroppedMalicious, "network_packets_dropped_malicious_count", "")                                        \
  X(PacketsDroppedBad, "network_packets_dropped_bad_count", "")                                                    \
  X(PacketsDroppedRlpBad, "network_packets_dropped_rlp_bad_count", "")                                             \
  X(PacketsDroppedUnknownError, "network_packets_dropped_unknown_count", "")                                       \
  X(PacketsPillarVoteReceived, "network_packets_pillarvote_received_count", "")                                    \
  X(PacketsPillarVoteProcessed, "network_packets_pillarvote_processed_count", "")                                  \
  X(PacketsPillarVoteSent, "network_packets_pillarvote_sent_count", "")                                            \
  X(PacketsPillarVoteDroppedIrrelevant, "network_packets_pillarvote_dropped_irrelevant_count", "")                 \
  X(PacketsPillarVoteDroppedInvalid, "network_packets_pillarvote_dropped_invalid_count", "")                       \
  X(PacketsPillarVoteDroppedOldPeriod, "network_packets_pillarvote_dropped_old_count", "")                         \
  X(PacketsPillarVoteBundleReceived, "network_packets_pillarvote_bundle_received_count", "")                       \
  X(PacketsPillarVoteBundleDroppedOldPeriod, "network_packets_pillarvote_bundle_dropped_old_count", "")            \
  X(PacketsPillarVoteBundleDroppedTooLarge, "network_packets_pillarvote_bundle_dropped_large_count", "")           \
  X(PacketsPillarVoteGetBundleReceived, "network_packets_pillarvote_get_bundle_received_count", "")                \
  X(PacketsPillarVoteGetBundleDroppedOldPeriod, "network_packets_pillarvote_get_bundle_dropped_old_count", "")     \
  X(PacketsPillarVoteGetBundleDroppedWrongPeriod, "network_packets_pillarvote_get_bundle_dropped_wrong_count", "") \
  X(PacketsPillarVoteGetBundleDroppedEmpty, "network_packets_pillarvote_get_bundle_dropped_empty_count", "")       \
  X(PacketsPillarVoteBundleSent, "network_packets_pillarvote_bundle_sent_count", "")                               \
  X(PacketsPillarVoteBundleRequested, "network_packets_pillarvote_bundle_requested_count", "")                     \
  X(PacketsDagReceived, "network_packets_dag_received_count", "")                                                  \
  X(PacketsDagVerified, "network_packets_dag_verified_count", "")                                                  \
  X(PacketsDagSent, "network_packets_dag_sent_count", "")                                                          \
  X(PacketsDagSentFailed, "network_packets_dag_sent_failed_count", "")                                             \
  X(PacketsDagRequested, "network_packets_dag_requested_count", "")                                                \
  X(PacketsDagRequestSent, "network_packets_dag_request_sent_count", "")                                           \
  X(PacketsDagDroppedKnown, "network_packets_dag_dropped_known_count", "")                                         \
  X(PacketsDagDroppedMissingTx, "network_packets_dag_dropped_missing_tx_count", "")                                \
  X(PacketsDagDroppedAheadBlock, "network_packets_dag_dropped_ahead_block_count", "")                              \
  X(PacketsDagDroppedVdfFailed, "network_packets_dag_dropped_vdf_failed_count", "")                                \
  X(PacketsDagDroppedFutureBlock, "network_packets_dag_dropped_future_block_count", "")                            \
  X(PacketsDagDroppedNotEligible, "network_packets_dag_dropped_not_eligible_count", "")                            \
  X(PacketsDagDroppedExpired, "network_packets_dag_dropped_expired_count", "")                                     \
  X(PacketsDagDroppedTxEstimation, "network_packets_dag_dropped_tx_estimation_count", "")                          \
  X(PacketsDagDroppedBlockTooBig, "network_packets_dag_dropped_block_big_count", "")                               \
  X(PacketsDagDroppedTipsVerifyFailed, "network_packets_dag_dropped_tips_verify_count", "")                        \
  X(PacketsDagDroppedMissingTip, "network_packets_dag_dropped_missing_tip_count", "")                              \
  X(PacketsDagRequestFailedNoMatch, "network_packets_dag_request_failed_no_match_count", "")                       \
  X(PacketsDagRequestFailedNoPeers, "network_packets_dag_request_failed_no_peers_count", "")                       \
  X(PacketsDagRequestFailedSynced, "network_packets_dag_request_failed_synced_count", "")                          \
  X(PacketsDagRequestFailedOngoing, "network_packets_dag_request_failed_ongoing_count", "")                        \
  X(PacketsDagRequestFailedPeriod, "network_packets_dag_request_failed_period_count", "")                          \
  X(PacketsDagSyncReceived, "network_packets_dag_sync_received_count", "")                                         \
  X(PacketsDagSyncVerified, "network_packets_dag_sync_verified_count", "")                                         \
  X(PacketsDagSyncDroppedSend, "network_packets_dag_sync_dropped_send_count", "")                                  \
  X(PacketsDagSyncDroppedSendNoPeers, "network_packets_dag_sync_dropped_send_no_peers_count", "")                  \
  X(PacketsDagSyncDroppedPast, "network_packets_dag_sync_dropped_past_count", "")                                  \
  X(PacketsDagSyncDroppedFuture, "network_packets_dag_sync_dropped_future_count", "")                              \
  X(PacketsDagSyncDroppedTxInvalid, "network_packets_dag_sync_dropped_tx_invalid_count", "")                       \
  X(PacketsDagSyncDroppedVerifyFailed, "network_packets_dag_sync_dropped_verify_count", "")                        \
  X(PacketsDagSyncDroppedInvalid, "network_packets_dag_sync_dropped_invalid_count", "")                            \
  X(PacketsDagGetSyncReceived, "network_packets_dag_get_sync_received_count", "")                                  \
  X(PacketsDagGetSyncDroppedNotAllowed, "network_packets_dag_get_sync_dropped_not_allowed_count", "")              \
  X(PacketsDagGetSyncSent, "network_packets_dag_get_sync_sent_count", "")                                          \
  X(PacketsVoteReceived, "network_packets_vote_received_count", "")                                                \
  X(PacketsVoteBundleReceived, "network_packets_vote_bundle_received_count", "")                                   \
  X(PacketsVoteGetNextReceived, "network_packets_vote_get_next_received_count", "")                                \
  X(PacketsVotesReceived, "network_packets_votes_received_count", "")                                              \
  X(PacketsVotesBadActor, "network_packets_votes_bad_actor_count", "")                                             \
  X(PacketsVotesDuplicate, "network_packets_votes_duplicate_count", "")                                            \
  X(PacketsVotesInvalid, "network_packets_votes_invalid_count", "")                                                \
  X(PacketsVotesDoubleVote, "network_packets_votes_double_vote_count", "")                                         \
  X(PacketsVotesBadSignature, "network_packets_votes_bad_signature_count", "")                                     \
  X(PacketsVotesQueueRace, "network_packets_votes_queue_race_count", "")                                           \
  X(PacketsPbftSyncReceived, "network_packets_pbft_sync_received_count", "")                                       \
  X(PacketsPbftGetSyncReceived, "network_packets_pbft_get_sync_received_count", "")                                \
  X(PacketsPbftBundleReceived, "network_packets_pbft_bundle_received_count", "")                                   \
  X(PacketsPbftBundleTooLarge, "network_packets_pbft_bundle_too_large_count", "")                                  \
  X(PacketsPbftBundleUnexpectedPeer, "network_packets_pbft_bundle_unexpected_peer_count", "")                      \
  X(PacketsPbftBundleNonUnique, "network_packets_pbft_bundle_non_unique_count", "")                                \
  X(PacketsPbftBundleBadActor, "network_packets_pbft_bundle_bad_actor_count", "")                                  \
  X(PacketsStatusReceived, "network_packets_status_received_count", "")                                            \
  X(PacketsTxReceived, "network_packets_tx_received_count", "")

class NetworkMetrics : public MetricsGroup {
 public:
  inline static const std::string group_name = "network";
  NetworkMetrics(std::shared_ptr<prometheus::Registry> registry) : MetricsGroup(std::move(registry)) {}

  ADD_COUNTERS_AND_ACCESSORS(NETWORK_METRICS_COUNTERS)

  ADD_GAUGE_METRIC_WITH_UPDATER(setPeersCount, "peers_count", "Count of peers that node is connected to")
  ADD_GAUGE_METRIC_WITH_UPDATER(setDiscoveredPeersCount, "discovered_peers_count", "Count of discovered peers")
  ADD_GAUGE_METRIC_WITH_UPDATER(setSyncingDuration, "syncing_duration_sec", "Time node is currently in sync state")
};

}  // namespace taraxa::metrics
