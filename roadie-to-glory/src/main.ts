import Phaser from 'phaser';
import { BootScene } from './scenes/BootScene';
import { PreloadScene } from './scenes/PreloadScene';
import { RustyAmpScene } from './scenes/RustyAmpScene';
import { BackAlleyScene } from './scenes/BackAlleyScene';
import { UIScene } from './ui/UIScene';

const config: Phaser.Types.Core.GameConfig = {
  type: Phaser.AUTO,
  width: 960,
  height: 540,
  parent: 'game-container',
  pixelArt: true,
  backgroundColor: '#1a1a2e',
  scene: [BootScene, PreloadScene, RustyAmpScene, BackAlleyScene, UIScene],
  scale: {
    mode: Phaser.Scale.FIT,
    autoCenter: Phaser.Scale.CENTER_BOTH
  }
};

new Phaser.Game(config);
