#!/bin/csh

set script_path = "/home/genesis/Documents/dpo_compare"

set CURR_OS = `uname -s`

if ($CURR_OS == "Linux") then
$script_path/dpo_automation
else
$script_path/dpo_automation.exe
endif
