use std::collections::HashMap;
use std::sync::mpsc::{self, TryRecvError};

use prometheus::{Encoder, IntGauge, Registry};

use lazy_static::lazy_static;

lazy_static! {
    static ref NETWORK_REGISTRY: Registry = Registry::new_custom(Some("network".to_string()), Some(HashMap::new())).unwrap();
    static ref NETWORK_PEERS_COUNTER: IntGauge = IntGauge::new("peers_count", "Count of peers that node is connected to").unwrap();
    static ref NETWORK_DISCOVERED_PEERS_COUNTER: IntGauge = IntGauge::new("discovered_peers_count", "Count of discovered peers").unwrap();
    static ref NETWORK_SYNCING_DURATION_SEC: IntGauge = IntGauge::new("syncing_duration_sec", "Time node is currently in sync state").unwrap();

    static ref PBFT_REGISTRY: Registry = Registry::new_custom(Some("pbft".to_string()), Some(HashMap::new())).unwrap();
    static ref PBFT_PERIOD: IntGauge = IntGauge::new("period", "Current PBFT period").unwrap();
    static ref PBFT_ROUND: IntGauge = IntGauge::new("round", "Current PBFT round").unwrap();
    static ref PBFT_STEP: IntGauge = IntGauge::new("step", "Current PBFT step").unwrap();
    static ref PBFT_VOTES_COUNT: IntGauge = IntGauge::new("votes_count", "Current node votes count").unwrap();
    static ref PBFT_BLOCK_NUMBER: IntGauge = IntGauge::new("block_number", "Number of the most recent block").unwrap();
    static ref PBFT_BLOCK_TRANSACTION_COUNT: IntGauge = IntGauge::new("block_transactions_count", "Number of transactions in block").unwrap();
    static ref PBFT_BLOCK_TIMESTAMP: IntGauge = IntGauge::new("block_timestamp", "Block timestamp").unwrap();

    static ref TRANSACTION_QUEUE_REGISTRY: Registry = Registry::new_custom(Some("transaction_queue".to_string()), Some(HashMap::new())).unwrap();
    static ref TRANSACTION_QUEUE_TRANSACTIONS_COUNT: IntGauge = IntGauge::new("transactions_count", "Transactions count in transactions queue").unwrap();
    static ref TRANSACTION_QUEUE_GAS_PRICE: IntGauge = IntGauge::new("gas_price", "Current gas price").unwrap();
}

extern  "C" {
   fn get_network_peers_count() -> i64;
}

type Callback = unsafe extern "C" fn() -> i64;
static mut callback_: Option<Callback> = None;

#[no_mangle]
pub extern "C" fn register_network_peers_counter_callback(callback: Callback) {
    unsafe {
        callback_ = Some(callback);
    }
}

#[no_mangle]
pub extern "C" fn start_metric_service() {
    // transaction_queue
    // pbft
    // network
    NETWORK_REGISTRY.register(Box::new(NETWORK_PEERS_COUNTER.clone())).unwrap();
    unsafe {
        //NETWORK_PEERS_COUNTER.set(get_network_peers_count());
        NETWORK_PEERS_COUNTER.set(callback_.unwrap()());
    }
    let mut buffer = Vec::<u8>::new();
    let encoder = prometheus::TextEncoder::new();
    encoder
        .encode(&NETWORK_REGISTRY.gather(), &mut buffer)
        .unwrap();
    println!("## Network registry");
    println!("{}", String::from_utf8(buffer.clone()).unwrap());

    /*
    thread::spawn(move || loop {
        NETWORK_PEERS_COUNTER.set(get_network_peers_count());


        thread::sleep(Duration::from_millis(500));
        match rx.try_recv() {
            Ok(_) | Err(TryRecvError::Disconnected) => {
                println!("Terminating.");
                break;
            }
            Err(TryRecvError::Empty) => {}
        }
    });
    */
}

#[no_mangle]
pub extern "C" fn stop_metric_service() {
}
