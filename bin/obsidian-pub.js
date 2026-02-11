#!/usr/bin/env node

/**
 * obsidian-pub CLI (Node.js version)
 * Simple wrapper for the vault management tools
 */

const { execSync } = require('child_process');
const path = require('path');
const fs = require('fs');

const commands = {
  sync: 'Sync vault with git',
  backup: 'Create vault backup',
  stats: 'Show vault statistics',
  init: 'Initialize new vault',
  help: 'Show this help message'
};

function showHelp() {
  console.log('Obsidian Pub CLI');
  console.log('================\n');
  console.log('Usage: obsidian-pub <command>\n');
  console.log('Commands:');
  Object.entries(commands).forEach(([cmd, desc]) => {
    console.log(`  ${cmd.padEnd(10)} - ${desc}`);
  });
}

function main() {
  const args = process.argv.slice(2);
  const command = args[0];

  if (!command || command === 'help' || command === '--help' || command === '-h') {
    showHelp();
    process.exit(0);
  }

  const makefilePath = path.join(process.cwd(), 'Makefile');
  
  if (!fs.existsSync(makefilePath)) {
    console.error('Error: Not in an obsidian-pub repository');
    console.error('Run this command from the root of your obsidian-pub vault');
    process.exit(1);
  }

  try {
    execSync(`make ${command}`, { stdio: 'inherit' });
  } catch (error) {
    console.error(`Error executing command: ${command}`);
    process.exit(1);
  }
}

main();
