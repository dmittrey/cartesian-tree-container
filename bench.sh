#!/bin/sh

mkdir -p bench
echo "Start recording metrics from countless"
./build/countless-bench > bench/countless.csv
echo "Recorded into bench/countless.csv"
echo "Start recording metrics from findkth"
./build/findkth-bench > bench/findkth.csv
echo "Recorded into bench/findkth.csv"