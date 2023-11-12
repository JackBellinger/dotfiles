#!/usr/bin/env zsh

function startvm() {
    aws ec2 start-instances --instance-ids=$1
}
function stopvm() {
    aws ec2 stop-instances --instance-ids=$1
}