#pragma once

#include "packet_handler.hpp"
#include "pillar_chain/pillar_chain_manager.hpp"

namespace taraxa::network::tarcap {

template <class PacketType>
class ExtPillarVotePacketHandler : public PacketHandler<PacketType> {
 public:
  ExtPillarVotePacketHandler(const FullNodeConfig& conf, std::shared_ptr<PeersState> peers_state,
                             std::shared_ptr<TimePeriodPacketsStats> packets_stats,
                             std::shared_ptr<pillar_chain::PillarChainManager> pillar_chain_manager,
                             const addr_t& node_addr, PrometheusPacketStats& prometheus_packet_stats,
                             const std::string& log_channel)
      : PacketHandler<PacketType>(conf, std::move(peers_state), std::move(packets_stats), node_addr,
                                  prometheus_packet_stats, log_channel),
        pillar_chain_manager_{std::move(pillar_chain_manager)},
        prometheus_packet_stats_{prometheus_packet_stats} {}

 protected:
  bool processPillarVote(const std::shared_ptr<PillarVote>& vote, const std::shared_ptr<TaraxaPeer>& peer) {
    if (!pillar_chain_manager_->isRelevantPillarVote(vote)) {
      ++prometheus_packet_stats_.dropped_pillar_irrelevant_vote;
      LOG(this->log_dg_) << "Drop irrelevant pillar vote " << vote->getHash() << ", period " << vote->getPeriod()
                         << " from peer " << peer->getId();
      return false;
    }

    if (!pillar_chain_manager_->validatePillarVote(vote)) {
      ++prometheus_packet_stats_.dropped_pillar_invalid_vote;
      // TODO: enable for mainnet
      // std::ostringstream err_msg;
      // err_msg << "Invalid pillar vote " << vote->getHash() << " from peer " << peer->getId();
      // throw MaliciousPeerException(err_msg.str());
      return false;
    }

    ++prometheus_packet_stats_.processed_pillar_vote;

    pillar_chain_manager_->addVerifiedPillarVote(vote);

    // Mark pillar vote as known for peer
    peer->markPillarVoteAsKnown(vote->getHash());
    return true;
  }

 protected:
  std::shared_ptr<pillar_chain::PillarChainManager> pillar_chain_manager_;

  PrometheusPacketStats& prometheus_packet_stats_;
};

}  // namespace taraxa::network::tarcap
