#include "network/tarcap/packets_handlers/latest/pillar_vote_packet_handler.hpp"

#include "vote/pillar_vote.hpp"

namespace taraxa::network::tarcap {

PillarVotePacketHandler::PillarVotePacketHandler(const FullNodeConfig &conf, std::shared_ptr<PeersState> peers_state,
                                                 std::shared_ptr<TimePeriodPacketsStats> packets_stats,
                                                 std::shared_ptr<pillar_chain::PillarChainManager> pillar_chain_manager,
                                                 const addr_t &node_addr,
                                                 PrometheusPacketStats &prometheus_packet_stats,
                                                 const std::string &logs_prefix)
    : ExtPillarVotePacketHandler(conf, std::move(peers_state), std::move(packets_stats),
                                 std::move(pillar_chain_manager), node_addr, prometheus_packet_stats,
                                 logs_prefix + "PILLAR_VOTE_PH") {}

void PillarVotePacketHandler::process(PillarVotePacket &&packet, const std::shared_ptr<TaraxaPeer> &peer) {
  ++prometheus_packet_stats_.received_pillar_vote;
  if (!kConf.genesis.state.hardforks.ficus_hf.isFicusHardfork(packet.pillar_vote->getPeriod())) {
    ++prometheus_packet_stats_.dropped_pillar_old_period_vote;
    std::ostringstream err_msg;
    err_msg << "Pillar vote " << packet.pillar_vote->getHash() << ", period " << packet.pillar_vote->getPeriod()
            << " < ficus hardfork block num";
    throw MaliciousPeerException(err_msg.str());
  }

  if (processPillarVote(packet.pillar_vote, peer)) {
    onNewPillarVote(packet.pillar_vote);
  }
}

void PillarVotePacketHandler::onNewPillarVote(const std::shared_ptr<PillarVote> &vote, bool rebroadcast) {
  for (const auto &peer : peers_state_->getAllPeers()) {
    if (peer.second->syncing_) {
      LOG(log_dg_) << "Pillar vote " << vote->getHash() << ", period " << vote->getPeriod() << " not sent to "
                   << peer.first << ". Peer syncing";
      continue;
    }

    if (peer.second->isPillarVoteKnown(vote->getHash()) && !rebroadcast) {
      continue;
    }

    sendPillarVote(peer.second, vote);
  }
}

void PillarVotePacketHandler::sendPillarVote(const std::shared_ptr<TaraxaPeer> &peer,
                                             const std::shared_ptr<PillarVote> &vote) {
  ++prometheus_packet_stats_.send_pillar_vote;
  if (sealAndSend(peer->getId(), SubprotocolPacketType::kPillarVotePacket, encodePacketRlp(PillarVotePacket(vote)))) {
    peer->markPillarVoteAsKnown(vote->getHash());
    LOG(log_dg_) << "Pillar vote " << vote->getHash() << ", period " << vote->getPeriod() << " sent to "
                 << peer->getId();
  }
}

}  // namespace taraxa::network::tarcap
