#!/bin/bash

ps -ef | grep -E "(mainboard|cyber_launch|)" | grep -v grep | awk '{print $2}' | xargs kill
sleep 2
ps -ef | grep -E "(mainboard|cyber_launch)" | grep -v grep | awk '{print $2}' | xargs kill -9
