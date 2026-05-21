# Cloudflare Workers

## Environment and bindings

  * Type bindings via `worker-configuration.d.ts`; access `env` from handlers.
  * Manage secrets with Wrangler; never commit `.env`.

## Handlers and responses

  * Always return explicit `Response` with correct status and content-type.
  * JSON error envelope shape: `{ error: { code, message } }`.
  * Add `requestId` to logs and responses when relevant.

## Caching and performance

  * Use the CF Cache API for GET where safe; respect cache headers.
  * Set timeouts and guard large payloads; be mindful of CPU limits.

## Testing and local dev

  * Mock bindings in tests (see `test/utils/mockWorkers.ts`).
  * Keep local and prod configs in sync via `wrangler.json`.
