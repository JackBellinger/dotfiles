# Logging and observability

## Logging

  * Structured logs: `{ level, msg, requestId, context }`.
  * Redact secrets and PII; never log tokens.

## Errors

  * Distinguish user vs system errors; map to HTTP status appropriately.
  * Include `requestId` and minimal context; avoid leaking internals.

## Tracing/metrics

  * If/when tracing is added, propagate correlation IDs consistently.
