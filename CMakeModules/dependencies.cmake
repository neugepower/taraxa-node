find_package(PkgConfig REQUIRED)

# find and include system libraries used in submodules and libraries
find_package(OpenSSL REQUIRED)
find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(prometheus-cpp REQUIRED)

pkg_check_modules(LZ4 REQUIRED liblz4)
pkg_check_modules(CRYPTOCPP REQUIRED libcryptopp)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include(FetchContent)

# Note that all settings below are defined with 'CACHE INTERNAL'. Otherwise
# the options declated in the sub-projects will override this value.

# ff
set(PERFORMANCE OFF CACHE INTERNAL "")
set(CURVE ALT_BN128 CACHE INTERNAL "")
set(USE_PT_COMPRESSION OFF CACHE INTERNAL "")
set(WITH_PROCPS OFF CACHE INTERNAL "")

FetchContent_Declare(
  ff
  GIT_REPOSITORY https://github.com/scipr-lab/libff.git
  GIT_TAG 5835b8c # v0.2.1
  GIT_SHALLOW TRUE
  FIND_PACKAGE_ARGS)

FetchContent_MakeAvailable(ff)

unset(PERFORMANCE CACHE)
unset(CURVE CACHE)
unset(USE_PT_COMPRESSION CACHE)
unset(WITH_PROCPS CACHE)

# Boost
set(BOOST_ENABLE_CMAKE ON CACHE INTERNAL "")

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.83.0
  GIT_SHALLOW TRUE
  FIND_PACKAGE_ARGS)

FetchContent_MakeAvailable(Boost)

unset(BOOST_ENABLE_CMAKE CACHE)

# cppgraphqlgen
set(GRAPHQL_BUILD_TESTS OFF CACHE INTERNAL "")
set(GRAPHQL_UPDATE_VERSION OFF CACHE INTERNAL "")
set(GRAPHQL_UPDATE_SAMPLES OFF CACHE INTERNAL "")
set(GRAPHQL_BUILD_CLIENTGEN OFF CACHE INTERNAL "")

FetchContent_Declare(
  cppgraphqlgen
  GIT_REPOSITORY https://github.com/microsoft/cppgraphqlgen.git
  GIT_TAG 1d659227bfc51fb7d9bb5dc9862234e7cfd1b1e3 # v4.5.4
  GIT_SHALLOW TRUE
  FIND_PACKAGE_ARGS)

FetchContent_MakeAvailable(cppgraphqlgen)

unset(GRAPHQL_BUILD_TESTS CACHE)
unset(GRAPHQL_UPDATE_VERSION CACHE)
unset(GRAPHQL_UPDATE_SAMPLES CACHE)
unset(GRAPHQL_BUILD_CLIENTGEN CACHE)

# RocksDB
set(WITH_LZ4 ON CACHE INTERNAL "")
set(USE_RTTI ON CACHE INTERNAL "")
set(FAIL_ON_WARNINGS OFF CACHE INTERNAL "")
set(WITH_TESTS OFF CACHE INTERNAL "")
set(WITH_BENCHMARK_TOOLS OFF CACHE INTERNAL "")

FetchContent_Declare(
  RocksDB
  GIT_REPOSITORY https://github.com/facebook/rocksdb.git
  GIT_TAG da11a59 # v6.29.5
  GIT_SHALLOW TRUE
  FIND_PACKAGE_ARGS)

FetchContent_MakeAvailable(RocksDB)

unset(WITH_LZ4 CACHE)
unset(USE_RTTI CACHE)
unset(FAIL_ON_WARNINGS CACHE)
unset(WITH_TESTS CACHE)
unset(WITH_BENCHMARK_TOOLS CACHE)

# other external dependencies
include(ProjectJSONRPCCPP)
