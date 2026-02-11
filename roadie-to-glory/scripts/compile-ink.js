#!/usr/bin/env node

/**
 * compile-ink.js
 *
 * Compiles all .ink source files in src/ink/ to .ink.json using the inkjs Compiler.
 * Output JSON files are written alongside the source files for direct import by the game.
 *
 * Usage:
 *   node scripts/compile-ink.js           # compile all .ink files
 *   node scripts/compile-ink.js sal.ink   # compile a specific file
 */

const fs = require('fs');
const path = require('path');

const { Compiler } = require('inkjs/compiler/Compiler');
const { CompilerOptions } = require('inkjs/compiler/CompilerOptions');
const { PosixFileHandler } = require('inkjs/compiler/FileHandler/PosixFileHandler');

const INK_DIR = path.resolve(__dirname, '..', 'src', 'ink');
const BOM = '\u{feff}';

function compileInkFile(inkFilePath) {
  const filename = path.basename(inkFilePath);
  const dir = path.dirname(inkFilePath);
  const outputPath = inkFilePath + '.json';

  console.log(`  Compiling: ${filename}`);

  // Read the ink source
  const inkSource = fs.readFileSync(inkFilePath, 'utf-8').replace(BOM, '');

  // Set up error handling
  const errors = [];
  const warnings = [];

  const errorHandler = (message, errorType) => {
    // errorType: 0 = Author, 1 = Warning, 2 = Error
    if (errorType === 2) {
      errors.push(message);
    } else if (errorType === 1) {
      warnings.push(message);
    }
  };

  // Set up file handler for INCLUDE resolution
  const fileHandler = new PosixFileHandler(dir);

  // Create compiler options
  const options = new CompilerOptions(
    filename,   // sourceFilename
    [],         // pluginNames
    false,      // countAllVisits
    errorHandler,
    fileHandler
  );

  // Compile
  const compiler = new Compiler(inkSource, options);
  let story = null;

  try {
    story = compiler.Compile();
  } catch (error) {
    if (error.message !== 'Compilation failed.') {
      throw error;
    }
  }

  // Report warnings
  if (warnings.length > 0) {
    console.log(`    Warnings (${warnings.length}):`);
    for (const w of warnings) {
      console.log(`      ${w}`);
    }
  }

  // Check for errors
  if (errors.length > 0 || !story) {
    console.error(`    FAILED with ${errors.length} error(s):`);
    for (const e of errors) {
      console.error(`      ${e}`);
    }
    return false;
  }

  // Serialize to JSON
  const jsonOutput = story.ToJson();
  if (!jsonOutput) {
    console.error(`    FAILED: Could not serialize story to JSON`);
    return false;
  }

  // Write the output file
  fs.writeFileSync(outputPath, jsonOutput, 'utf-8');

  const stats = compiler.GenerateStats();
  if (stats) {
    console.log(`    OK - words: ${stats.words}, knots: ${stats.knots}, stitches: ${stats.stitches}, functions: ${stats.functions}`);
  } else {
    console.log(`    OK`);
  }

  return true;
}

function main() {
  console.log('ink Compiler (inkjs)');
  console.log(`Source directory: ${INK_DIR}`);
  console.log('');

  // Determine which files to compile
  let inkFiles;
  const specificFile = process.argv[2];

  if (specificFile) {
    const fullPath = path.resolve(INK_DIR, specificFile);
    if (!fs.existsSync(fullPath)) {
      console.error(`File not found: ${fullPath}`);
      process.exit(1);
    }
    inkFiles = [fullPath];
  } else {
    // Find all .ink files (but not .ink.json files)
    const allFiles = fs.readdirSync(INK_DIR);
    inkFiles = allFiles
      .filter(f => f.endsWith('.ink') && !f.endsWith('.ink.json'))
      .map(f => path.join(INK_DIR, f))
      .sort();
  }

  if (inkFiles.length === 0) {
    console.log('No .ink files found.');
    process.exit(0);
  }

  console.log(`Found ${inkFiles.length} ink file(s) to compile.`);
  console.log('');

  let succeeded = 0;
  let failed = 0;

  for (const inkFile of inkFiles) {
    const ok = compileInkFile(inkFile);
    if (ok) {
      succeeded++;
    } else {
      failed++;
    }
  }

  console.log('');
  console.log(`Done. ${succeeded} succeeded, ${failed} failed.`);

  if (failed > 0) {
    process.exit(1);
  }
}

main();
