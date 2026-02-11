import Phaser from 'phaser';
import { gameState } from '../systems/GameState';
import { dialogueManager } from '../systems/DialogueManager';
import { PuzzleSystem } from '../systems/PuzzleSystem';

interface Hotspot {
  sprite: Phaser.GameObjects.Sprite | Phaser.GameObjects.Image;
  id: string;
  name: string;
  lookDescription: string;
  canPickUp: boolean;
  itemId?: string;
  itemName?: string;
  itemDescription?: string;
  canTalk: boolean;
  storyId?: string;
  canUse: boolean;
  useAction?: () => string | null;
  onPickUp?: () => void;
}

export class RustyAmpScene extends Phaser.Scene {
  private player!: Phaser.GameObjects.Sprite;
  private walkTarget: { x: number; y: number } | null = null;
  private isWalking = false;
  private walkSpeed = 150;
  private hotspots: Hotspot[] = [];
  private pendingAction: { verb: string; target: Hotspot } | null = null;
  private walkableArea = { minX: 40, maxX: 920, minY: 310, maxY: 440 };
  private walkAnimTimer: Phaser.Time.TimerEvent | null = null;
  private facingRight = true;

  constructor() {
    super({ key: 'RustyAmpScene' });
  }

  create(): void {
    gameState.currentScene = 'RustyAmpScene';

    // Background
    this.add.image(480, 270, 'bg_rustyamp').setDepth(0);

    // Stage area
    this.add.image(480, 300, 'stage').setDepth(1);

    // Dim stage lights (colored rectangles above stage)
    const lightColors = [0xff4444, 0x44ff44, 0x4444ff, 0xffff44];
    for (let i = 0; i < 4; i++) {
      const light = this.add.circle(300 + i * 120, 80, 8, lightColors[i], 0.4).setDepth(1);
      this.tweens.add({
        targets: light,
        alpha: { from: 0.2, to: 0.6 },
        duration: 1000 + i * 300,
        yoyo: true,
        repeat: -1
      });
    }

    // Scene title
    const titleText = this.add.text(480, 20, 'THE RUSTY AMP', {
      fontSize: '14px',
      color: '#cc4444',
      fontFamily: 'monospace',
      fontStyle: 'bold'
    }).setOrigin(0.5).setDepth(10).setAlpha(0.6);

    // Player
    this.player = this.add.sprite(
      gameState.playerPosition.x,
      gameState.playerPosition.y,
      'eddie'
    ).setDepth(5).setOrigin(0.5, 1);

    // Setup hotspots (interactable objects)
    this.setupHotspots();

    // Click to move / interact
    this.input.on('pointerdown', (pointer: Phaser.Input.Pointer) => {
      if (pointer.y > 460) return; // Don't move when clicking UI area

      const ui = this.scene.get('UIScene') as any;
      const verb = gameState.currentVerb;

      // Check if clicked on a hotspot
      const clicked = this.getHotspotAt(pointer.x, pointer.y);
      if (clicked) {
        this.handleHotspotClick(clicked, verb);
      } else {
        // Walk to point
        this.walkTo(pointer.x, pointer.y);
      }
    });

    // Listen for events from UI scene
    this.events.on('use-item-on-world', this.handleItemUse, this);

    // Fade in
    this.cameras.main.fadeIn(500, 0, 0, 0);

    // If this is a fresh start, trigger intro
    if (!gameState.getFlag('intro_done')) {
      this.time.delayedCall(800, () => {
        this.showMessage('Eddie: *looks around* Another day, another soundcheck at the world\'s least prestigious venue.');
        this.time.delayedCall(3000, () => {
          this.showMessage('Eddie: At least the cockroaches appreciate my work.');
          gameState.setFlag('intro_done', true);
        });
      });
    }
  }

  setupHotspots(): void {
    this.hotspots = [];

    // Speaker (hides the Battle of the Bands flyer)
    if (!gameState.isPuzzleSolved('move_speaker')) {
      const speaker = this.add.image(180, 340, 'speaker').setDepth(3).setInteractive();
      this.hotspots.push({
        sprite: speaker,
        id: 'speaker',
        name: 'Heavy Speaker',
        lookDescription: 'A speaker so heavy it probably has its own gravitational field. There seems to be something stuck underneath it.',
        canPickUp: false,
        canTalk: false,
        canUse: true,
        useAction: () => {
          if (PuzzleSystem.canSolve('move_speaker')) {
            const result = PuzzleSystem.solve('move_speaker');
            speaker.destroy();
            this.hotspots = this.hotspots.filter(h => h.id !== 'speaker');
            this.emitInventoryChanged();
            return result;
          }
          if (gameState.selectedItem?.id === 'crowbar') {
            const result = PuzzleSystem.solve('move_speaker');
            speaker.destroy();
            this.hotspots = this.hotspots.filter(h => h.id !== 'speaker');
            this.emitInventoryChanged();
            return result;
          }
          return 'Eddie pushes the speaker but it won\'t budge. He\'d need some kind of lever.';
        }
      });
    }

    // Broken mic on the stage
    if (!gameState.hasItem('broken_mic') && !gameState.isPuzzleSolved('fix_mic') && !gameState.hasItem('working_mic')) {
      const brokenMic = this.add.image(460, 290, 'broken_mic').setDepth(3).setInteractive();
      this.hotspots.push({
        sprite: brokenMic,
        id: 'broken_mic',
        name: 'Broken Microphone',
        lookDescription: 'A microphone that\'s seen better days. And better decades. The cable is frayed beyond belief.',
        canPickUp: false,
        canTalk: false,
        canUse: false
      });
    }

    // Mic stand
    const micStand = this.add.image(460, 308, 'mic_stand').setDepth(2).setInteractive();
    this.hotspots.push({
      sprite: micStand,
      id: 'mic_stand',
      name: 'Mic Stand',
      lookDescription: 'A mic stand that\'s more rust than stand. It\'s held together by hope and tetanus.',
      canPickUp: false,
      canTalk: false,
      canUse: true,
      useAction: () => {
        if (gameState.hasItem('working_mic') && !gameState.getFlag('sang_for_sal')) {
          gameState.setFlag('sang_for_sal', true);
          return 'Eddie places the mic on the stand and clears his throat. What comes out is... actually incredible. A raw, powerful riff that echoes through the venue. Even the cockroaches stop to listen.';
        }
        if (gameState.getFlag('sang_for_sal')) {
          return 'Eddie already had his moment of glory. No need to push it.';
        }
        return 'The stand is empty. It looks lonely. Like Eddie\'s love life.';
      }
    });

    // Duct tape on the bar counter
    if (!gameState.hasItem('duct_tape')) {
      const ductTape = this.add.image(680, 355, 'duct_tape').setDepth(3).setInteractive();
      this.hotspots.push({
        sprite: ductTape,
        id: 'duct_tape',
        name: 'Duct Tape',
        lookDescription: 'A roll of duct tape. The roadie\'s best friend, after coffee and self-loathing.',
        canPickUp: true,
        itemId: 'duct_tape',
        itemName: 'Duct Tape',
        itemDescription: 'A roll of duct tape. Fixes everything except Eddie\'s career.',
        canTalk: false,
        canUse: false,
        onPickUp: () => {
          ductTape.destroy();
          this.hotspots = this.hotspots.filter(h => h.id !== 'duct_tape');
        }
      });
    }

    // Mic cable behind the crate
    if (!gameState.hasItem('mic_cable')) {
      const micCable = this.add.image(120, 380, 'mic_cable').setDepth(3).setInteractive();
      this.hotspots.push({
        sprite: micCable,
        id: 'mic_cable',
        name: 'Mic Cable',
        lookDescription: 'A tangled mic cable. It\'s like a snake that gave up on life.',
        canPickUp: true,
        itemId: 'mic_cable',
        itemName: 'Mic Cable',
        itemDescription: 'A frayed but usable mic cable. Just needs some... creative repair.',
        canTalk: false,
        canUse: false,
        onPickUp: () => {
          micCable.destroy();
          this.hotspots = this.hotspots.filter(h => h.id !== 'mic_cable');
        }
      });
    }

    // Bar counter
    const barCounter = this.add.image(700, 370, 'bar_counter').setDepth(2).setInteractive();
    this.hotspots.push({
      sprite: barCounter,
      id: 'bar_counter',
      name: 'Bar Counter',
      lookDescription: 'A bar counter so sticky it could be classified as a new form of adhesive. There are mysterious stains that predate human civilization.',
      canPickUp: false,
      canTalk: false,
      canUse: false
    });

    // Poster on the wall
    const poster = this.add.image(350, 180, 'poster').setDepth(2).setInteractive();
    this.hotspots.push({
      sprite: poster,
      id: 'poster',
      name: 'Faded Poster',
      lookDescription: 'A poster for a band called "Temporary Deafness." Based on the venue, the name was probably a legal disclaimer.',
      canPickUp: false,
      canTalk: false,
      canUse: false
    });

    // Jukebox
    const jukebox = this.add.image(850, 340, 'jukebox').setDepth(3).setInteractive();
    this.hotspots.push({
      sprite: jukebox,
      id: 'jukebox',
      name: 'Jukebox',
      lookDescription: 'An ancient jukebox. The only songs it plays are "Heartbreak Hotel" and a mysterious track labeled "DO NOT PLAY." Naturally, someone has tried to play it 47 times.',
      canPickUp: false,
      canTalk: false,
      canUse: true,
      useAction: () => {
        return 'Eddie feeds it a coin. It makes a grinding noise, plays three notes of "Stairway to Heaven," then gives up. Fair enough.';
      }
    });

    // Crate near the back
    const crate = this.add.image(120, 360, 'crate').setDepth(2).setInteractive();
    this.hotspots.push({
      sprite: crate,
      id: 'crate',
      name: 'Equipment Crate',
      lookDescription: 'A wooden crate full of tangled cables. It\'s like a spaghetti factory had a fight with a computer store.',
      canPickUp: false,
      canTalk: false,
      canUse: false
    });

    // NPC: Sal the sound guy
    const sal = this.add.image(600, 350, 'sal').setDepth(4).setOrigin(0.5, 1).setInteractive();
    this.hotspots.push({
      sprite: sal,
      id: 'sal',
      name: 'Sal',
      lookDescription: 'Sal. The sound guy. He\'s been doing this so long he can hear frequencies that don\'t exist. His resting expression suggests he\'s heard them all, and none of them were good.',
      canPickUp: false,
      canTalk: true,
      storyId: 'sal',
      canUse: false
    });

    // NPC: Barkeep
    const barkeep = this.add.image(750, 358, 'barkeep').setDepth(4).setOrigin(0.5, 1).setInteractive();
    this.hotspots.push({
      sprite: barkeep,
      id: 'barkeep',
      name: 'Rick the Barkeep',
      lookDescription: 'Rick has been tending this bar since before Eddie was born. He communicates primarily through grunts and the occasional world-weary sigh.',
      canPickUp: false,
      canTalk: true,
      storyId: 'barkeep',
      canUse: false
    });

    // NPC: Groupie hanging around
    const groupie = this.add.image(300, 360, 'groupie').setDepth(4).setOrigin(0.5, 1).setInteractive();
    this.hotspots.push({
      sprite: groupie,
      id: 'groupie',
      name: 'Val the Superfan',
      lookDescription: 'Val is The Rusty Amp\'s only regular "fan." She\'s been waiting for "the next big thing" here for 15 years. Hope springs eternal. Or maybe it\'s just the draft from the broken window.',
      canPickUp: false,
      canTalk: true,
      storyId: 'groupie',
      canUse: false
    });

    // Door to Back Alley (scene transition)
    const door = this.add.image(920, 330, 'door').setDepth(3).setInteractive();
    this.hotspots.push({
      sprite: door,
      id: 'back_door',
      name: 'Back Door',
      lookDescription: 'A door leading to the back alley. The sign says "Emergency Exit" but at The Rusty Amp, every exit is an emergency.',
      canPickUp: false,
      canTalk: false,
      canUse: true,
      useAction: () => {
        this.transitionTo('BackAlleyScene');
        return null;
      }
    });

    // Right arrow hint for back alley
    const arrow = this.add.image(940, 380, 'arrow_right').setDepth(10).setAlpha(0.5).setInteractive();
    this.tweens.add({
      targets: arrow,
      x: 945,
      duration: 800,
      yoyo: true,
      repeat: -1
    });
    arrow.on('pointerdown', () => {
      this.transitionTo('BackAlleyScene');
    });

    // Add hover highlights to all hotspot sprites
    for (const hotspot of this.hotspots) {
      const sprite = hotspot.sprite;
      sprite.on('pointerover', () => {
        sprite.setTint(0xffffaa);
        this.emitHotspotName(hotspot.name);
      });
      sprite.on('pointerout', () => {
        sprite.clearTint();
        this.emitHotspotName('');
      });
    }
  }

  getHotspotAt(x: number, y: number): Hotspot | null {
    for (const hotspot of this.hotspots) {
      const bounds = hotspot.sprite.getBounds();
      if (bounds.contains(x, y)) {
        return hotspot;
      }
    }
    return null;
  }

  handleHotspotClick(hotspot: Hotspot, verb: string): void {
    // Walk to the hotspot first, then perform the action
    const targetX = Math.max(this.walkableArea.minX, Math.min(this.walkableArea.maxX, hotspot.sprite.x));
    const targetY = Math.max(this.walkableArea.minY, Math.min(this.walkableArea.maxY, hotspot.sprite.y + 30));

    this.pendingAction = { verb, target: hotspot };
    this.walkTo(targetX, targetY);
  }

  performAction(verb: string, hotspot: Hotspot): void {
    switch (verb) {
      case 'look':
        this.showMessage(`${hotspot.lookDescription}`);
        break;
      case 'talk':
        if (hotspot.canTalk && hotspot.storyId) {
          gameState.meetNPC(hotspot.id);
          this.startDialogue(hotspot.storyId);
        } else {
          this.showMessage(`Eddie talks to the ${hotspot.name}. It doesn't respond. Because it's not a person. Obviously.`);
        }
        break;
      case 'pickup':
        if (hotspot.canPickUp && hotspot.itemId) {
          gameState.addItem({
            id: hotspot.itemId,
            name: hotspot.itemName || hotspot.name,
            description: hotspot.itemDescription || hotspot.lookDescription
          });
          this.showMessage(`Picked up: ${hotspot.itemName || hotspot.name}`);
          this.emitInventoryChanged();
          if (hotspot.onPickUp) hotspot.onPickUp();
        } else {
          this.showMessage(`Eddie can't pick that up. It's either too heavy, too gross, or both.`);
        }
        break;
      case 'use':
        if (gameState.selectedItem) {
          this.handleItemUseOnHotspot(gameState.selectedItem.id, hotspot);
        } else if (hotspot.canUse && hotspot.useAction) {
          const result = hotspot.useAction();
          if (result) this.showMessage(result);
        } else {
          this.showMessage(`Eddie pokes at the ${hotspot.name}. Nothing happens. Story of his life.`);
        }
        break;
    }
  }

  handleItemUse(data: { itemId: string }): void {
    // Item used on the world, not on a specific hotspot
    this.showMessage('Eddie waves the item around. Nothing happens. He feels silly.');
  }

  handleItemUseOnHotspot(itemId: string, hotspot: Hotspot): void {
    // Special use combinations
    if (itemId === 'crowbar' && hotspot.id === 'speaker') {
      if (PuzzleSystem.canSolve('move_speaker')) {
        const result = PuzzleSystem.solve('move_speaker');
        if (result) {
          this.showMessage(result);
          hotspot.sprite.destroy();
          this.hotspots = this.hotspots.filter(h => h.id !== 'speaker');
          this.emitInventoryChanged();
          gameState.selectedItem = null;
        }
      }
    } else if (itemId === 'working_mic' && hotspot.id === 'mic_stand') {
      if (!gameState.getFlag('sang_for_sal')) {
        gameState.setFlag('sang_for_sal', true);
        this.showMessage('Eddie places the mic on the stand and clears his throat. What comes out is... actually incredible. A raw, powerful riff that echoes through the venue. Even the cockroaches stop to listen.');
        gameState.selectedItem = null;
      } else {
        this.showMessage('Eddie already had his moment of glory.');
      }
    } else {
      this.showMessage(`Using ${gameState.getItem(itemId)?.name || 'that'} on the ${hotspot.name} doesn't seem to do anything useful.`);
    }
  }

  walkTo(x: number, y: number): void {
    const targetX = Math.max(this.walkableArea.minX, Math.min(this.walkableArea.maxX, x));
    const targetY = Math.max(this.walkableArea.minY, Math.min(this.walkableArea.maxY, y));

    this.walkTarget = { x: targetX, y: targetY };
    this.isWalking = true;

    // Face the correct direction
    if (targetX > this.player.x) {
      this.player.setFlipX(false);
      this.facingRight = true;
    } else {
      this.player.setFlipX(true);
      this.facingRight = false;
    }

    // Simple walk animation via frame swapping
    if (this.walkAnimTimer) this.walkAnimTimer.destroy();
    let frame = 0;
    this.walkAnimTimer = this.time.addEvent({
      delay: 200,
      callback: () => {
        if (!this.isWalking) return;
        frame = (frame + 1) % 3;
        const keys = ['eddie', 'eddie_walk1', 'eddie_walk2'];
        this.player.setTexture(keys[frame]);
        if (!this.facingRight) this.player.setFlipX(true);
      },
      loop: true
    });
  }

  startDialogue(storyId: string): void {
    const ui = this.scene.get('UIScene');
    ui.events.emit('start-dialogue', storyId);
  }

  showMessage(text: string): void {
    const ui = this.scene.get('UIScene');
    ui.events.emit('show-message', text);
  }

  emitInventoryChanged(): void {
    const ui = this.scene.get('UIScene');
    ui.events.emit('inventory-changed');
  }

  emitHotspotName(name: string): void {
    const ui = this.scene.get('UIScene');
    ui.events.emit('hotspot-name', name);
  }

  transitionTo(sceneKey: string): void {
    gameState.playerPosition = { x: 80, y: 370 };
    this.cameras.main.fadeOut(400, 0, 0, 0);
    this.cameras.main.once('camerafadeoutcomplete', () => {
      this.scene.start(sceneKey);
    });
  }

  update(_time: number, delta: number): void {
    if (this.isWalking && this.walkTarget) {
      const dx = this.walkTarget.x - this.player.x;
      const dy = this.walkTarget.y - this.player.y;
      const dist = Math.sqrt(dx * dx + dy * dy);

      if (dist < 5) {
        this.player.x = this.walkTarget.x;
        this.player.y = this.walkTarget.y;
        this.isWalking = false;
        this.walkTarget = null;
        this.player.setTexture('eddie');
        if (!this.facingRight) this.player.setFlipX(true);
        if (this.walkAnimTimer) {
          this.walkAnimTimer.destroy();
          this.walkAnimTimer = null;
        }

        // Perform pending action if any
        if (this.pendingAction) {
          const { verb, target } = this.pendingAction;
          this.pendingAction = null;
          this.performAction(verb, target);
        }
      } else {
        const speed = this.walkSpeed * (delta / 1000);
        this.player.x += (dx / dist) * speed;
        this.player.y += (dy / dist) * speed;
      }

      // Update depth sorting based on Y position
      this.player.setDepth(Math.floor(this.player.y / 10));

      // Save position
      gameState.playerPosition = { x: this.player.x, y: this.player.y };
    }
  }
}
