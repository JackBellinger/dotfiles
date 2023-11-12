#!/usr/bin/env zsh

alias cc="cargo check"
alias ccl="cargo clippy --all-features --all-targets"
alias ct="cargo test -- --nocapture"
alias cf="cargo fmt"
alias cb="cargo build"
alias cbr="cargo build --release"
alias rbt1="export RUST_BACKTRACE=1"
alias rbt0="unset RUST_BACKTRACE"

function cbz() {
    local prev_flags=$(echo $RUSTFLAGS)
    export RUSTFLAGS="-Z macro-backtrace"
    cargo build
    export RUSTFLAGS=$prev_flags
}