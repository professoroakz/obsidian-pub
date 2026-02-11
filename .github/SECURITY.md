# Security Policy

## Supported Versions

We release patches for security vulnerabilities. Currently supported versions:

| Version | Supported          |
| ------- | ------------------ |
| 0.1.x   | :white_check_mark: |
| < 0.1   | :x:                |

## Reporting a Vulnerability

If you discover a security vulnerability, please follow these steps:

1. **DO NOT** open a public issue
2. Email the maintainers or create a private security advisory on GitHub
3. Include:
   - Description of the vulnerability
   - Steps to reproduce
   - Potential impact
   - Suggested fix (if any)

## Response Timeline

- **Initial Response**: Within 48 hours
- **Status Update**: Within 7 days
- **Fix Timeline**: Depends on severity
  - Critical: 24-48 hours
  - High: 7 days
  - Medium: 30 days
  - Low: 90 days

## Security Best Practices

When using this repository:

- Never commit sensitive information (API keys, passwords, tokens)
- Use `.env` files for secrets (already in `.gitignore`)
- Review scripts before execution
- Keep dependencies updated
- Use latest stable version

## Disclosure Policy

- Security issues are fixed privately
- Once patched, a security advisory will be published
- Credit will be given to reporters (if desired)

## Contact

For security concerns:

- Create a security advisory on GitHub
- Email: <professoroakz@users.noreply.github.com>

Thank you for helping keep obsidian-pub secure! 🔒
