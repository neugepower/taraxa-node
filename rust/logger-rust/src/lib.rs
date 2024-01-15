use std::ffi::CStr;
use std::os::raw::c_char;

extern crate slog;
extern crate slog_term;
extern crate slog_async;

use slog::*;

pub type AddrT = u32;

#[repr(i32)]
#[derive(Debug)]
#[derive(PartialEq, PartialOrd)]
pub enum VerbosityRust {
    Silent = -1,
    Error = 0,
    Warning = 1,
    Info = 2,
    Debug = 3,
    Trace = 4,
}

#[repr(C)]
#[derive(Debug)]
pub struct LoggerRust {
    logger: *mut slog::Logger,
    verbosity: VerbosityRust,
    channel: *const c_char,
}

//struct CustomFormatDrain;
//
//impl Drain for CustomFormatDrain {
//    type Err = slog::Never;
//    type Ok = ();
//
//    fn log(&self, record: &Record, logger_values: &OwnedKVList) -> result::Result<Self::Ok, Self::Err> {
//        //let node = logger_values.get("node").unwrap();
//        //let channel = logger_values.get("channel").unwrap();
//        println!(
//            "{} {} [{}] {}: {}",
//            "node",
//            "channel",
//            "DATE",
//            "TEST",
//            record.msg(),
//        );
//        Ok(())
//    }
//}

#[no_mangle]
pub extern "C" fn createLoggerRust(
    verbosity: VerbosityRust,
    channel: *const c_char,
    node_id: AddrT,
) -> LoggerRust {
    let decorator = slog_term::TermDecorator::new().build();
    let drain = slog_term::FullFormat::new(decorator).build().fuse();
    let drain = slog_async::Async::new(drain).build().fuse();

    let logger = Box::new(slog::Logger::root(drain, o!("node" => node_id.to_string())));
    let logger_ptr = Box::into_raw(logger);

    LoggerRust {
        logger: logger_ptr,
        verbosity: verbosity,
        channel: channel,
    }
}

#[no_mangle]
pub extern "C" fn sink(logger: LoggerRust, msg: *const c_char) {
    if logger.verbosity > VerbosityRust::Info {
        return
    }

    let slice = unsafe { CStr::from_ptr(msg) };

    unsafe { (*logger.logger).log(&Record::new(
        &record_static!(verbosity_to_level(logger.verbosity), ""),
        &format_args!("{}", slice.to_str().unwrap()),
        b!(),
    ))};
}

fn verbosity_to_level(verbosity: VerbosityRust) -> Level {
    match verbosity {
        VerbosityRust::Silent => Level::Critical,
        VerbosityRust::Error => Level::Error,
        VerbosityRust::Warning => Level::Warning,
        VerbosityRust::Info => Level::Info,
        VerbosityRust::Debug => Level::Debug,
        VerbosityRust::Trace => Level::Trace,
    }
}
