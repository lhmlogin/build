#!/usr/bin/perl

for($i=2;$i<=100;$i++) {
    # print("cp sliver_repair.c plugin${i}.c\n");
    `cp sliver_repair.c plugin${i}.c`;
    `sed -i 's/sliver_repair/plugin'${i}'/'g plugin${i}.c`;
}