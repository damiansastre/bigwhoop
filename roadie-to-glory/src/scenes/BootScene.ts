import Phaser from 'phaser';

export class BootScene extends Phaser.Scene {
  constructor() {
    super({ key: 'BootScene' });
  }

  preload(): void {
    // Nothing to load in boot — we generate placeholder art programmatically
  }

  create(): void {
    this.scene.start('PreloadScene');
  }
}
