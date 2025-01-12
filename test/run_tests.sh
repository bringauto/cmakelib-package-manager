#!/bin/sh

set -e

app_tests() {
    set -e
    cmake -DTEST_WITH_DESTDIR=OFF -P ./run_app_tests.cmake
    cmake -DTEST_WITH_DESTDIR=ON  -P ./run_app_tests.cmake
}

var_tests() {
    set -e
    cmake -DINVALID_VAR_TEST=OFF -P ./run_vars_test.cmake

    set +e
    cmake -DINVALID_VAR_TEST=ON -P ./run_vars_test.cmake
    if [ $? -eq 0 ]; then
        echo "run_vars_test failed!" >&2
        exit 1
    fi
    set -e
}

app_tests
var_tests