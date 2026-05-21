# Testing (Vitest)

## Structure

  * Keep tests alongside code or under `test/` mirrors.
  * Name tests `*.test.ts`; group by feature.

## Practices

  * Unit tests for logic; integration tests for Workers routes.
  * Use `test/utils/mockWorkers.ts` to mock env/bindings.
  * Minimal snapshot testing; prefer explicit assertions.
  * Aim for agreed coverage threshold; fail CI if below.
