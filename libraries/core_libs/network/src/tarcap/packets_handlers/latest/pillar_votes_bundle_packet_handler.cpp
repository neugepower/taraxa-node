#include "network/tarcap/packets_handlers/latest/pillar_votes_bundle_packet_handler.hpp"

#include "vote/pillar_vote.hpp"

namespace taraxa::network::tarcap {

PillarVotesBundlePacketHandler::PillarVotesBundlePacketHandler(
    const FullNodeConfig &conf, std::shared_ptr<PeersState> peers_state,
    std::shared_ptr<TimePeriodPacketsStats> packets_stats,
    std::shared_ptr<pillar_chain::PillarChainManager> pillar_chain_manager, const addr_t &node_addr,
    PrometheusPacketStats &prometheus_packet_stats, const std::string &logs_prefix)
    : ExtPillarVotePacketHandler(conf, std::move(peers_state), std::move(packets_stats),
                                 std::move(pillar_chain_manager), node_addr, prometheus_packet_stats,
                                 logs_prefix + "PILLAR_VOTES_BUNDLE_PH") {}

void PillarVotesBundlePacketHandler::process(PillarVotesBundlePacket &&packet,
                                             const std::shared_ptr<TaraxaPeer> &peer) {
  ++prometheus_packet_stats_.received_pillar_bundle_vote;
  if (packet.pillar_votes_bundle.pillar_votes.size() == 0 ||
      packet.pillar_votes_bundle.pillar_votes.size() > kMaxPillarVotesInBundleRlp) {
    ++prometheus_packet_stats_.dropped_pillar_bundle_too_large_vote;
    throw InvalidRlpItemsCountException("PillarVotesBundlePacket", packet.pillar_votes_bundle.pillar_votes.size(),
                                        kMaxPillarVotesInBundleRlp);
  }

  // TODO[2744]: there could be the same protection as in pbft syncing that only requested bundle packet is accepted
  LOG(log_dg_) << "PillarVotesBundlePacket received from peer " << peer->getId();

  for (const auto &pillar_vote : packet.pillar_votes_bundle.pillar_votes) {
    if (!kConf.genesis.state.hardforks.ficus_hf.isFicusHardfork(pillar_vote->getPeriod())) {
      ++prometheus_packet_stats_.dropped_pillar_bundle_old_period_vote;
      std::ostringstream err_msg;
      err_msg << "Synced pillar vote " << pillar_vote->getHash() << ", period " << pillar_vote->getPeriod()
              << " < ficus hardfork block num";
      throw MaliciousPeerException(err_msg.str());
    }

    processPillarVote(pillar_vote, peer);
  }
}

}  // namespace taraxa::network::tarcap
