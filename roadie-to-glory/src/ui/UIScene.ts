import Phaser from 'phaser';
import { gameState } from '../systems/GameState';
import { dialogueManager, DialogueResult } from '../systems/DialogueManager';
import { ItemCombiner } from '../systems/ItemCombiner';
import { SaveLoadSystem } from '../systems/SaveLoad';

const VERB_BAR_Y = 468;
const INVENTORY_BAR_Y = 504;
const UI_BG_COLOR = 0x111122;
const VERB_COLOR = '#aaaacc';
const VERB_ACTIVE_COLOR = '#ffff44';
const INVENTORY_SLOT_SIZE = 40;

const VERBS = [
  { id: 'look', label: 'Look' },
  { id: 'talk', label: 'Talk' },
  { id: 'pickup', label: 'Pick Up' },
  { id: 'use', label: 'Use' }
];

// Monkey Island-style character colors
const SPEAKER_COLORS: Record<string, string> = {
  'sal': '#cc8844',
  'barkeep': '#88aa66',
  'rick': '#88aa66',
  'val': '#ee66cc',
  'groupie': '#ee66cc',
  'eddie': '#6699ee',
  'narrator': '#ffffff',
};

// Map storyId to the NPC's hotspot id
const STORY_TO_NPC: Record<string, string> = {
  'sal': 'sal',
  'barkeep': 'barkeep',
  'groupie': 'groupie',
};

export class UIScene extends Phaser.Scene {
  private verbTexts: Map<string, Phaser.GameObjects.Text> = new Map();
  private inventorySlots: Phaser.GameObjects.Container[] = [];
  private messageText!: Phaser.GameObjects.Text;
  private messageTimer: Phaser.Time.TimerEvent | null = null;
  private dialogueContainer!: Phaser.GameObjects.Container;
  private hotspotLabel!: Phaser.GameObjects.Text;
  private isDialogueOpen = false;
  private saveButton!: Phaser.GameObjects.Text;
  private loadButton!: Phaser.GameObjects.Text;
  private activeStoryNpc: string | null = null;
  private dialogueLines: { text: string; speaker: string }[] = [];
  private dialogueLineIndex = 0;
  private dialogueChoices: { text: string; index: number }[] = [];

  constructor() {
    super({ key: 'UIScene' });
  }

  create(): void {
    // Dark UI background bar
    const uiBg = this.add.rectangle(480, 490, 960, 80, UI_BG_COLOR).setDepth(0);
    const uiBorder = this.add.rectangle(480, 460, 960, 2, 0x333355).setDepth(1);

    // Verb bar
    this.createVerbBar();

    // Inventory bar
    this.createInventoryBar();

    // Message text area (above UI bar)
    this.messageText = this.add.text(480, 440, '', {
      fontSize: '13px',
      color: '#ffffff',
      fontFamily: 'monospace',
      wordWrap: { width: 800 },
      align: 'center',
      backgroundColor: '#000000aa',
      padding: { x: 12, y: 6 }
    }).setOrigin(0.5, 1).setDepth(100).setAlpha(0);

    // Hotspot name label
    this.hotspotLabel = this.add.text(480, 454, '', {
      fontSize: '11px',
      color: '#ffff88',
      fontFamily: 'monospace',
      align: 'center'
    }).setOrigin(0.5).setDepth(100);

    // Dialogue container (hidden by default)
    this.dialogueContainer = this.add.container(0, 0).setDepth(200).setVisible(false);

    // Save/Load buttons
    this.saveButton = this.add.text(900, 470, '[SAVE]', {
      fontSize: '10px',
      color: '#666688',
      fontFamily: 'monospace'
    }).setDepth(50).setInteractive({ useHandCursor: true });
    this.saveButton.on('pointerdown', () => this.saveGame());
    this.saveButton.on('pointerover', () => this.saveButton.setColor('#aaaacc'));
    this.saveButton.on('pointerout', () => this.saveButton.setColor('#666688'));

    this.loadButton = this.add.text(900, 484, '[LOAD]', {
      fontSize: '10px',
      color: '#666688',
      fontFamily: 'monospace'
    }).setDepth(50).setInteractive({ useHandCursor: true });
    this.loadButton.on('pointerdown', () => this.loadGame());
    this.loadButton.on('pointerover', () => this.loadButton.setColor('#aaaacc'));
    this.loadButton.on('pointerout', () => this.loadButton.setColor('#666688'));

    // Listen for events from game scenes
    this.events.on('show-message', this.showMessage, this);
    this.events.on('start-dialogue', this.startDialogue, this);
    this.events.on('inventory-changed', this.refreshInventory, this);
    this.events.on('hotspot-name', this.showHotspotName, this);

    // Set default verb
    this.setActiveVerb('look');

    // Initial inventory render
    this.refreshInventory();
  }

  createVerbBar(): void {
    const startX = 60;
    const spacing = 100;

    VERBS.forEach((verb, i) => {
      const text = this.add.text(startX + i * spacing, VERB_BAR_Y, verb.label, {
        fontSize: '14px',
        color: VERB_COLOR,
        fontFamily: 'monospace',
        fontStyle: 'bold'
      }).setOrigin(0, 0).setDepth(10).setInteractive({ useHandCursor: true });

      text.on('pointerdown', () => {
        this.setActiveVerb(verb.id);
        gameState.selectedItem = null;
      });

      text.on('pointerover', () => {
        if (gameState.currentVerb !== verb.id) {
          text.setColor('#ccccee');
        }
      });

      text.on('pointerout', () => {
        if (gameState.currentVerb !== verb.id) {
          text.setColor(VERB_COLOR);
        }
      });

      this.verbTexts.set(verb.id, text);
    });
  }

  setActiveVerb(verbId: string): void {
    gameState.currentVerb = verbId;
    this.verbTexts.forEach((text, id) => {
      text.setColor(id === verbId ? VERB_ACTIVE_COLOR : VERB_COLOR);
    });
  }

  createInventoryBar(): void {
    // Inventory label
    this.add.text(460, VERB_BAR_Y, 'Inventory:', {
      fontSize: '12px',
      color: '#666688',
      fontFamily: 'monospace'
    }).setDepth(10);
  }

  refreshInventory(): void {
    // Clear existing slots
    this.inventorySlots.forEach(slot => slot.destroy());
    this.inventorySlots = [];

    const startX = 460;
    const slotY = INVENTORY_BAR_Y;

    gameState.inventory.forEach((item, i) => {
      const container = this.add.container(startX + i * (INVENTORY_SLOT_SIZE + 4), slotY).setDepth(10);

      // Slot background
      const bg = this.add.rectangle(0, 0, INVENTORY_SLOT_SIZE, INVENTORY_SLOT_SIZE - 8, 0x222244, 0.8)
        .setStrokeStyle(1, 0x444466)
        .setInteractive({ useHandCursor: true });

      // Item name text
      const label = this.add.text(0, 0, item.name.substring(0, 4), {
        fontSize: '8px',
        color: '#ccccee',
        fontFamily: 'monospace',
        align: 'center'
      }).setOrigin(0.5);

      container.add([bg, label]);

      // Click to select item
      bg.on('pointerdown', (pointer: Phaser.Input.Pointer) => {
        if (pointer.rightButtonDown()) {
          // Right-click: look at item
          this.showMessage(`${item.name}: ${item.description}`);
        } else {
          // Left click
          if (gameState.selectedItem && gameState.selectedItem.id !== item.id) {
            // Try to combine items
            const result = ItemCombiner.combine(gameState.selectedItem.id, item.id);
            this.showMessage(result.message);
            gameState.selectedItem = null;
            this.refreshInventory();
          } else if (gameState.selectedItem?.id === item.id) {
            // Deselect
            gameState.selectedItem = null;
            bg.setStrokeStyle(1, 0x444466);
          } else {
            // Select this item
            gameState.selectedItem = item;
            gameState.currentVerb = 'use';
            this.setActiveVerb('use');
            this.refreshInventory();
          }
        }
      });

      bg.on('pointerover', () => {
        bg.setFillStyle(0x333366, 0.9);
        this.showHotspotName(item.name);
      });

      bg.on('pointerout', () => {
        bg.setFillStyle(0x222244, 0.8);
        this.showHotspotName('');
      });

      // Highlight selected item
      if (gameState.selectedItem?.id === item.id) {
        bg.setStrokeStyle(2, 0xffff44);
      }

      this.inventorySlots.push(container);
    });
  }

  showMessage(text: string): void {
    if (!text) return;
    if (this.messageTimer) this.messageTimer.destroy();

    this.messageText.setText(text);
    this.messageText.setAlpha(1);

    // Auto-hide after a duration based on text length
    const duration = Math.max(3000, text.length * 40);
    this.messageTimer = this.time.delayedCall(duration, () => {
      this.tweens.add({
        targets: this.messageText,
        alpha: 0,
        duration: 500
      });
    });
  }

  showHotspotName(name: string): void {
    this.hotspotLabel.setText(name);
  }

  startDialogue(storyId: string): void {
    const result = dialogueManager.startStory(storyId);
    if (!result) return;
    this.isDialogueOpen = true;
    this.activeStoryNpc = STORY_TO_NPC[storyId] || storyId;

    // Parse all lines into {text, speaker} pairs
    this.dialogueLines = [];
    for (const line of result.lines) {
      const parsed = this.parseSpeaker(line.text);
      this.dialogueLines.push(parsed);
    }
    this.dialogueChoices = result.choices;
    this.dialogueLineIndex = 0;

    this.showNextBubble();
  }

  parseSpeaker(text: string): { text: string; speaker: string } {
    // Match "Name: dialogue" pattern
    const match = text.match(/^([A-Z][a-z]+)\s*:\s*(.+)$/s);
    if (match) {
      return { speaker: match[1].toLowerCase(), text: match[2] };
    }
    // Narration — no speaker prefix
    return { speaker: 'narrator', text };
  }

  getCharacterWorldPos(id: string): { x: number; y: number } | null {
    const currentScene = gameState.currentScene;
    const scene = this.scene.get(currentScene) as any;
    if (scene && typeof scene.getCharacterPosition === 'function') {
      return scene.getCharacterPosition(id);
    }
    return null;
  }

  showNextBubble(): void {
    this.dialogueContainer.removeAll(true);
    this.dialogueContainer.setVisible(true);

    // Transparent click-catcher overlay (no darkening)
    const overlay = this.add.rectangle(480, 270, 960, 540, 0x000000, 0)
      .setInteractive();
    this.dialogueContainer.add(overlay);

    // Are there lines left to show?
    if (this.dialogueLineIndex < this.dialogueLines.length) {
      const line = this.dialogueLines[this.dialogueLineIndex];
      this.showSpeechBubble(line.speaker, line.text);

      overlay.on('pointerdown', () => {
        this.dialogueLineIndex++;
        this.showNextBubble();
      });
    } else if (this.dialogueChoices.length > 0) {
      // All lines shown, now show choices near Eddie
      this.showChoices(this.dialogueChoices);
    } else {
      // Nothing left — close
      this.closeDialogue();
    }
  }

  showSpeechBubble(speaker: string, text: string): void {
    const maxWidth = 280;
    const padding = 10;
    const color = SPEAKER_COLORS[speaker] || '#ffffff';

    // Determine position — above the speaking character
    let posX: number;
    let posY: number;

    if (speaker === 'narrator') {
      // Narration: show above the NPC being talked to
      const npcPos = this.activeStoryNpc ? this.getCharacterWorldPos(this.activeStoryNpc) : null;
      if (npcPos) {
        posX = npcPos.x;
        posY = npcPos.y - 8;
      } else {
        posX = 480;
        posY = 120;
      }
    } else if (speaker === 'eddie') {
      const eddiePos = this.getCharacterWorldPos('eddie');
      if (eddiePos) {
        posX = eddiePos.x;
        posY = eddiePos.y - 8;
      } else {
        posX = 200;
        posY = 260;
      }
    } else {
      // NPC speaker — try to find by name matching hotspot/story id
      const npcPos = this.getCharacterWorldPos(speaker) || (this.activeStoryNpc ? this.getCharacterWorldPos(this.activeStoryNpc) : null);
      if (npcPos) {
        posX = npcPos.x;
        posY = npcPos.y - 8;
      } else {
        posX = 480;
        posY = 120;
      }
    }

    // Clamp so bubble stays on screen
    posX = Math.max(maxWidth / 2 + 10, Math.min(960 - maxWidth / 2 - 10, posX));
    posY = Math.max(30, Math.min(280, posY));

    // Speech text
    const speechText = this.add.text(posX, posY, text, {
      fontSize: '13px',
      color: color,
      fontFamily: 'monospace',
      fontStyle: 'bold',
      wordWrap: { width: maxWidth },
      align: 'center',
      stroke: '#000000',
      strokeThickness: 3,
    }).setOrigin(0.5, 1).setDepth(201);
    this.dialogueContainer.add(speechText);

    // Background bubble behind text
    const bounds = speechText.getBounds();
    const bg = this.add.rectangle(
      bounds.centerX, bounds.centerY,
      bounds.width + padding * 2, bounds.height + padding * 2,
      0x000000, 0.5
    ).setStrokeStyle(1, 0x444488).setDepth(200);
    this.dialogueContainer.add(bg);
    this.dialogueContainer.sendToBack(bg);

    // Keep overlay at very back
    const overlayObj = this.dialogueContainer.getAt(0);
    this.dialogueContainer.sendToBack(overlayObj);
  }

  showChoices(choices: { text: string; index: number }[]): void {
    // Show player choices near Eddie's position, slightly above the UI bar
    const eddiePos = this.getCharacterWorldPos('eddie');
    const baseX = eddiePos ? Math.max(180, Math.min(780, eddiePos.x)) : 480;
    const baseY = eddiePos ? Math.min(eddiePos.y - 8, 260) : 200;

    const maxWidth = 300;
    let yOff = baseY;

    for (const choice of choices) {
      const choiceText = this.add.text(baseX, yOff, `> ${choice.text}`, {
        fontSize: '13px',
        color: SPEAKER_COLORS['eddie'],
        fontFamily: 'monospace',
        fontStyle: 'bold',
        wordWrap: { width: maxWidth },
        align: 'left',
        stroke: '#000000',
        strokeThickness: 3,
      }).setOrigin(0.5, 1).setDepth(201).setInteractive({ useHandCursor: true });

      const bgChoice = this.add.rectangle(
        choiceText.getBounds().centerX, choiceText.getBounds().centerY,
        choiceText.getBounds().width + 16, choiceText.getBounds().height + 8,
        0x000000, 0.5
      ).setStrokeStyle(1, 0x444488).setDepth(200);

      choiceText.on('pointerover', () => {
        choiceText.setColor('#ffff88');
      });
      choiceText.on('pointerout', () => {
        choiceText.setColor(SPEAKER_COLORS['eddie']);
      });
      choiceText.on('pointerdown', () => {
        const nextResult = dialogueManager.chooseChoice(choice.index);
        if (nextResult) {
          if (nextResult.lines.length === 0 && nextResult.choices.length === 0) {
            this.closeDialogue();
          } else {
            // Feed new lines/choices into the bubble system
            this.dialogueLines = [];
            for (const line of nextResult.lines) {
              this.dialogueLines.push(this.parseSpeaker(line.text));
            }
            this.dialogueChoices = nextResult.choices;
            this.dialogueLineIndex = 0;
            this.showNextBubble();
          }
        } else {
          this.closeDialogue();
        }
      });

      this.dialogueContainer.add(bgChoice);
      this.dialogueContainer.add(choiceText);
      yOff -= choiceText.height + 12;
    }
  }

  showDialogue(result: DialogueResult): void {
    // Legacy entry point — redirect to bubble system
    this.dialogueLines = [];
    for (const line of result.lines) {
      this.dialogueLines.push(this.parseSpeaker(line.text));
    }
    this.dialogueChoices = result.choices;
    this.dialogueLineIndex = 0;
    this.showNextBubble();
  }

  closeDialogue(): void {
    this.dialogueContainer.removeAll(true);
    this.dialogueContainer.setVisible(false);
    this.isDialogueOpen = false;
    dialogueManager.endDialogue();
    this.refreshInventory();
  }

  saveGame(): void {
    const inkState = dialogueManager.getStoryState();
    SaveLoadSystem.save(inkState);
    this.showMessage('Game saved.');
  }

  loadGame(): void {
    const saveData = SaveLoadSystem.load();
    if (saveData) {
      this.showMessage('Game loaded.');
      // Restart the current scene
      const currentScene = gameState.currentScene;
      this.scene.stop(currentScene === 'RustyAmpScene' ? 'BackAlleyScene' : 'RustyAmpScene');
      this.scene.start(currentScene);
      this.refreshInventory();
    } else {
      this.showMessage('No save file found.');
    }
  }
}
