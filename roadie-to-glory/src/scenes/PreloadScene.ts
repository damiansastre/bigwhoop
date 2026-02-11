import Phaser from 'phaser';
import { dialogueManager } from '../systems/DialogueManager';

// Import ink story JSON files
import salStory from '../ink/sal.ink.json';
import barkeepStory from '../ink/barkeep.ink.json';
import groupieStory from '../ink/groupie.ink.json';
import worldStory from '../ink/world.ink.json';

export class PreloadScene extends Phaser.Scene {
  constructor() {
    super({ key: 'PreloadScene' });
  }

  preload(): void {
    // Show loading text
    const text = this.add.text(480, 270, 'Loading...', {
      fontSize: '24px',
      color: '#ffffff',
      fontFamily: 'monospace'
    }).setOrigin(0.5);

    // Generate all placeholder sprites as textures
    this.generatePlaceholderSprites();
  }

  generatePlaceholderSprites(): void {
    // Eddie - the protagonist (simple character shape)
    this.generateCharacterSprite('eddie', 0x4488cc, 24, 48);
    this.generateCharacterSprite('eddie_walk1', 0x4488cc, 24, 48, true);
    this.generateCharacterSprite('eddie_walk2', 0x4488cc, 24, 48, false, true);

    // NPCs
    this.generateCharacterSprite('sal', 0x886644, 28, 48);
    this.generateCharacterSprite('barkeep', 0x668844, 26, 44);
    this.generateCharacterSprite('groupie', 0xcc44aa, 22, 46);

    // Objects
    this.generateObjectSprite('speaker', 0x333333, 48, 56);
    this.generateObjectSprite('mic_stand', 0x888888, 8, 52);
    this.generateObjectSprite('broken_mic', 0xaa4444, 12, 16);
    this.generateObjectSprite('duct_tape', 0xcccc44, 14, 10);
    this.generateObjectSprite('mic_cable', 0x222222, 20, 12);
    this.generateObjectSprite('crowbar', 0x555599, 28, 8);
    this.generateObjectSprite('stage', 0x553322, 300, 24);
    this.generateObjectSprite('bar_counter', 0x664422, 200, 40);
    this.generateObjectSprite('door', 0x774433, 40, 64);
    this.generateObjectSprite('poster', 0xcc8844, 24, 32);
    this.generateObjectSprite('jukebox', 0x996633, 32, 48);
    this.generateObjectSprite('crate', 0x775533, 32, 28);
    this.generateObjectSprite('dumpster', 0x446644, 64, 48);
    this.generateObjectSprite('cat', 0xff8800, 20, 16);
    this.generateObjectSprite('flyer_ground', 0xccccaa, 16, 12);
    this.generateObjectSprite('toolbox', 0xcc3333, 28, 20);
    this.generateObjectSprite('arrow_left', 0xffff00, 24, 24);
    this.generateObjectSprite('arrow_right', 0xffff00, 24, 24);

    // Inventory item icons (small)
    this.generateObjectSprite('inv_duct_tape', 0xcccc44, 24, 20);
    this.generateObjectSprite('inv_mic_cable', 0x222222, 28, 20);
    this.generateObjectSprite('inv_crowbar', 0x555599, 32, 12);
    this.generateObjectSprite('inv_working_mic', 0x88cc88, 16, 24);
    this.generateObjectSprite('inv_botb_flyer', 0xccccaa, 20, 24);
    this.generateObjectSprite('inv_guitar_string', 0xdddddd, 28, 8);

    // Backgrounds (large colored rectangles with details)
    this.generateBackground('bg_rustyamp', 0x1a0a0a, 0x2a1515);
    this.generateBackground('bg_backalley', 0x0a0a1a, 0x151525);
  }

  generateCharacterSprite(key: string, color: number, w: number, h: number, lean1 = false, lean2 = false): void {
    const g = this.add.graphics();
    // Body
    g.fillStyle(color);
    g.fillRect(4, h * 0.3, w - 8, h * 0.5);
    // Head
    const headColor = Phaser.Display.Color.IntegerToColor(color);
    g.fillStyle(Phaser.Display.Color.GetColor(
      Math.min(255, headColor.red + 40),
      Math.min(255, headColor.green + 40),
      Math.min(255, headColor.blue + 40)
    ));
    g.fillCircle(w / 2 + (lean1 ? 2 : lean2 ? -2 : 0), h * 0.22, w * 0.35);
    // Legs
    g.fillStyle(0x222244);
    const legOffset = lean1 ? 3 : lean2 ? -3 : 0;
    g.fillRect(w * 0.25 + legOffset, h * 0.75, 4, h * 0.25);
    g.fillRect(w * 0.6 - legOffset, h * 0.75, 4, h * 0.25);
    g.generateTexture(key, w, h);
    g.destroy();
  }

  generateObjectSprite(key: string, color: number, w: number, h: number): void {
    const g = this.add.graphics();
    g.fillStyle(color);
    g.fillRoundedRect(0, 0, w, h, 2);
    // Highlight
    g.fillStyle(0xffffff, 0.15);
    g.fillRect(2, 2, w - 4, h * 0.3);
    g.generateTexture(key, w, h);
    g.destroy();
  }

  generateBackground(key: string, floorColor: number, wallColor: number): void {
    const g = this.add.graphics();
    const w = 960;
    const h = 540;
    // Wall
    g.fillStyle(wallColor);
    g.fillRect(0, 0, w, h * 0.55);
    // Floor
    g.fillStyle(floorColor);
    g.fillRect(0, h * 0.55, w, h * 0.45);
    // Floor line
    g.lineStyle(1, 0x333333, 0.5);
    g.lineBetween(0, h * 0.55, w, h * 0.55);
    // Some wall details
    g.lineStyle(1, 0x444444, 0.3);
    for (let i = 0; i < 5; i++) {
      const bx = 80 + i * 200;
      g.strokeRect(bx, 40, 120, 80);
    }
    g.generateTexture(key, w, h);
    g.destroy();
  }

  create(): void {
    // Load ink stories into the dialogue manager
    dialogueManager.loadStory('sal', salStory);
    dialogueManager.loadStory('barkeep', barkeepStory);
    dialogueManager.loadStory('groupie', groupieStory);
    dialogueManager.loadStory('world', worldStory);

    // Start the game
    this.scene.start('RustyAmpScene');
    this.scene.launch('UIScene');
  }
}
