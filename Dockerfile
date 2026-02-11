# Multi-stage Dockerfile for obsidian-pub
# Supports both Python CLI and general vault management

FROM python:3.11-slim as base

# Set working directory
WORKDIR /workspace

# Install system dependencies
RUN apt-get update && apt-get install -y \
    git \
    make \
    curl \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Install Python package
COPY pyproject.toml setup.py ./
COPY obsidian_pub ./obsidian_pub
RUN pip install --no-cache-dir -e .

# Copy scripts and configuration
COPY scripts ./scripts
COPY Makefile ./
COPY .editorconfig ./
COPY .gitignore ./

# Set executable permissions
RUN chmod +x scripts/*.sh 2>/dev/null || true

# Configure git (can be overridden)
RUN git config --global user.name "Obsidian Pub" && \
    git config --global user.email "obsidian-pub@docker"

# Default command
CMD ["/bin/bash"]

# Development stage
FROM base as dev

# Install development dependencies
RUN pip install --no-cache-dir -e ".[dev]"

# Install Node.js for markdown linting
RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && \
    apt-get install -y nodejs && \
    npm install -g markdown-link-check

# Production stage
FROM base as prod

# Cleanup unnecessary files
RUN rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Set user to non-root
RUN useradd -m -u 1000 obsidian
USER obsidian

# Volume for vault data
VOLUME ["/workspace"]

# Entrypoint
ENTRYPOINT ["obsidian-pub"]
