# prochotctl

prochotctl is a small utility to allow the user to toggle the `BD_PROCHOT` signal, which is used to throttle the speed on processors.

Often, the throttling is caused by a bogus reason, such as using an unofficial power adapter for a laptop.

## Notice

This tool only runs on Linux! There's no version for Windows (yet).

## Building

To build prochotctl, simply run `./build.sh`.

## Usage

The program is very simple to use:

Turn on BD_PROCHOT: `prochotctl on`

Turn off BD_PROCHOT: `prochotctl off`

## Tested Machines

Tested on a MacBook Air 2014 with an Intel i5-4260U processor, where the lack of a battery caused the CPU to throttle significantly.