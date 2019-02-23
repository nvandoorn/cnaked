#!/usr/bin/env bash

test() {
  make test
}


test
while sleep 5; do test; done
