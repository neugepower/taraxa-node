#pragma once

#include <atomic>
#include <cstdint>

namespace taraxa::network::tarcap {

struct PrometheusPacketStats {
  // generic
  std::atomic<uint32_t> received = 0;
  std::atomic<uint32_t> received_thread_pool = 0;
  std::atomic<uint32_t> dropped_too_early = 0;
  std::atomic<uint32_t> dropped_syncing = 0;
  std::atomic<uint32_t> dropped_peers_processing_time_too_high = 0;
  std::atomic<uint32_t> dropped_wrong_tarcap_version = 0;
  std::atomic<uint32_t> dropped_peer_lost = 0;
  std::atomic<uint32_t> dropped_malicious_peer = 0;
  std::atomic<uint32_t> dropped_packet_bad = 0;
  std::atomic<uint32_t> dropped_rlp_bad = 0;
  std::atomic<uint32_t> dropped_unknown_error = 0;

  // pillar
  std::atomic<uint32_t> received_pillar_vote = 0;
  std::atomic<uint32_t> processed_pillar_vote = 0;
  std::atomic<uint32_t> send_pillar_vote = 0;
  std::atomic<uint32_t> dropped_pillar_irrelevant_vote = 0;
  std::atomic<uint32_t> dropped_pillar_invalid_vote = 0;
  std::atomic<uint32_t> dropped_pillar_old_period_vote = 0;
  std::atomic<uint32_t> received_pillar_bundle_vote = 0;
  std::atomic<uint32_t> dropped_pillar_bundle_old_period_vote = 0;
  std::atomic<uint32_t> dropped_pillar_bundle_too_large_vote = 0;
  std::atomic<uint32_t> received_get_pillar_bundle_vote = 0;
  std::atomic<uint32_t> dropped_get_pillar_bundle_old_period_vote = 0;
  std::atomic<uint32_t> dropped_get_pillar_bundle_wrong_period_vote = 0;
  std::atomic<uint32_t> dropped_get_pillar_bundle_empty_vote = 0;
  std::atomic<uint32_t> send_pillar_bundle_vote = 0;
  std::atomic<uint32_t> request_pillar_bundle_vote = 0;

  // dag
  std::atomic<uint32_t> received_dag = 0;
  std::atomic<uint32_t> dropped_known_dag = 0;
  std::atomic<uint32_t> send_dag = 0;
  std::atomic<uint32_t> failed_send_dag = 0;
  std::atomic<uint32_t> verified_dag = 0;
  std::atomic<uint32_t> dropped_missing_transactions_dag = 0;
  std::atomic<uint32_t> dropped_ahead_dag = 0;
  std::atomic<uint32_t> dropped_failed_vdf_verification_dag = 0;
  std::atomic<uint32_t> dropped_future_dag = 0;
  std::atomic<uint32_t> dropped_not_eligible_dag = 0;
  std::atomic<uint32_t> dropped_expired_dag = 0;
  std::atomic<uint32_t> dropped_incorrect_transactions_estimation_dag = 0;
  std::atomic<uint32_t> dropped_too_big_dag = 0;
  std::atomic<uint32_t> dropped_failed_tips_verification_dag = 0;
  std::atomic<uint32_t> dropped_missing_tip_dag = 0;
  std::atomic<uint32_t> request_dag = 0;
  std::atomic<uint32_t> request_send_dag = 0;
  std::atomic<uint32_t> request_failed_no_peer_match_dag = 0;
  std::atomic<uint32_t> request_failed_no_peers_dag = 0;
  std::atomic<uint32_t> request_failed_already_requested_from_peer_dag = 0;
  std::atomic<uint32_t> request_failed_unmatched_period_dag = 0;
  std::atomic<uint32_t> dropped_send_sync_dag = 0;
  std::atomic<uint32_t> dropped_send_no_peers_dag = 0;
  std::atomic<uint32_t> received_sync_dag = 0;
  std::atomic<uint32_t> verified_sync_dag = 0;
  std::atomic<uint32_t> dropped_past_period_sync_dag = 0;
  std::atomic<uint32_t> dropped_future_period_sync_dag = 0;
  std::atomic<uint32_t> dropped_tx_invalid_sync_dag = 0;
  std::atomic<uint32_t> dropped_invalid_verify_sync_dag = 0;
  std::atomic<uint32_t> dropped_invalid_sync_dag = 0;
  std::atomic<uint32_t> received_get_sync_dag = 0;
  std::atomic<uint32_t> dropped_not_allowed_get_sync_dag = 0;
  std::atomic<uint32_t> send_get_sync_dag = 0;

  // votes
  std::atomic<uint32_t> received_vote = 0;
  std::atomic<uint32_t> received_votes_bundle = 0;
  std::atomic<uint32_t> received_get_next_votes = 0;

  // pbft
  std::atomic<uint32_t> received_pbft_sync = 0;
  std::atomic<uint32_t> received_get_pbft_sync = 0;

  // status
  std::atomic<uint32_t> received_status = 0;

  // tx
  std::atomic<uint32_t> received_tx = 0;

  ////////////////////////////

  // packet queue sizes
  std::atomic<uint32_t> queue_size_low = 0;
  std::atomic<uint32_t> queue_size_mid = 0;
  std::atomic<uint32_t> queue_size_high = 0;
};

}  // namespace taraxa::network::tarcap
