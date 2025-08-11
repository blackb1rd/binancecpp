# TODO - Future Improvements

## High Priority

### Core API Completeness

- [ ] Complete missing market data endpoints (historical trades, klines, etc.)
- [ ] Implement advanced trading features (OCO orders, SOR, cancel/replace)
- [ ] Add margin trading support (cross & isolated margin)
- [ ] Complete wallet endpoints (deposit, withdraw, asset management)

### Performance & Modern C++

- [ ] Investigate replacing libcurl with modern alternatives:
  - [uWebSockets](https://github.com/uNetworking/uWebSockets) (WebSocket improvements)
- [ ] Consider JSON parsing performance improvements:
  - [simdjson](https://simdjson.org/) (faster JSON parsing)

## Medium Priority

### Developer Experience

- [ ] Add comprehensive unit tests for all endpoints
- [ ] Create interactive examples and tutorials
- [ ] Add CMake package config for easier integration
- [ ] Pre-built packages for major platforms

### Code Quality

- [ ] Implement async/await patterns for better performance
- [ ] Add request rate limiting and retry logic
- [ ] Implement proper error handling and custom exceptions
- [ ] Add metrics and monitoring integration

## Low Priority

### Advanced Features

- [ ] Connection pooling for HTTP requests
- [ ] WebSocket connection auto-reconnection
- [ ] Request/response compression support
- [ ] Memory pool allocation for high-frequency trading
- [ ] VS Code extension with IntelliSense support
