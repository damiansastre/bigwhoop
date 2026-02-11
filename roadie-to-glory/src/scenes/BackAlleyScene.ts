import Phaser from 'phaser';
import { gameState } from '../systems/GameState';

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
  canUse: boolean;
  useAction?: () => string | null;
  onPickUp?: () => void;
}

export class BackAlleyScene extends Phaser.Scene {
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
    super({ key: 'BackAlleyScene' });
  }

  create(): void {
    gameState.currentScene = 'BackAlleyScene';

    // Background
    this.add.image(480, 270, 'bg_backalley').setDepth(0);

    // Scene title
    this.add.text(480, 20, 'BACK ALLEY', {
      fontSize: '14px',
      color: '#4466aa',
      fontFamily: 'monospace',
      fontStyle: 'bold'
    }).setOrigin(0.5).setDepth(10).setAlpha(0.6);

    // Some alley atmosphere
    const rain = this.add.particles(0, 0, 'duct_tape', {
      x: { min: 0, max: 960 },
      y: -10,
      lifespan: 1500,
      speedY: { min: 100, max: 200 },
      scale: { start: 0.05, end: 0 },
      alpha: { start: 0.3, end: 0 },
      quantity: 1,
      frequency: 200
    }).setDepth(1);

    // Player
    this.player = this.add.sprite(
      gameState.playerPosition.x,
      gameState.playerPosition.y,
      'eddie'
    ).setDepth(5).setOrigin(0.5, 1);

    this.setupHotspots();

    // Click to move / interact
    this.input.on('pointerdown', (pointer: Phaser.Input.Pointer) => {
      if (pointer.y > 460) return;

      const verb = gameState.currentVerb;
      const clicked = this.getHotspotAt(pointer.x, pointer.y);
      if (clicked) {
        this.handleHotspotClick(clicked, verb);
      } else {
        this.walkTo(pointer.x, pointer.y);
      }
    });

    this.cameras.main.fadeIn(500, 0, 0, 0);
  }

  setupHotspots(): void {
    this.hotspots = [];

    // Dumpster
    const dumpster = this.add.image(700, 370, 'dumpster').setDepth(3).setInteractive();
    this.hotspots.push({
      sprite: dumpster,
      id: 'dumpster',
      name: 'Dumpster',
      lookDescription: 'A dumpster full of broken dreams and what appears to be a half-eaten burrito. Actually, this venue\'s entire business model fits in here.',
      canPickUp: false,
      canTalk: false,
      canUse: true,
      useAction: () => {
        if (!gameState.hasItem('guitar_string') && !gameState.getFlag('searched_dumpster')) {
          gameState.setFlag('searched_dumpster', true);
          gameState.addItem({
            id: 'guitar_string',
            name: 'Guitar String',
            description: 'A slightly used guitar string salvaged from a dumpster. Has character.'
          });
          this.emitInventoryChanged();
          return 'Eddie rummages through the dumpster. Among the regrets and pizza boxes, he finds a guitar string. It\'s slightly used, but then again, so is Eddie.';
        }
        if (gameState.getFlag('searched_dumpster')) {
          return 'Eddie\'s already been through the dumpster once. Twice would be a lifestyle choice.';
        }
        return 'Eddie peers into the dumpster. It peers back.';
      }
    });

    // Crowbar leaning against the wall
    if (!gameState.hasItem('crowbar')) {
      const crowbar = this.add.image(400, 395, 'crowbar').setDepth(3).setInteractive();
      this.hotspots.push({
        sprite: crowbar,
        id: 'crowbar',
        name: 'Crowbar',
        lookDescription: 'A rusty crowbar leaning against the wall. Gordon Freeman would be jealous. Or maybe not — this one\'s pretty janky.',
        canPickUp: true,
        itemId: 'crowbar',
        itemName: 'Crowbar',
        itemDescription: 'A rusty crowbar. Good for prying things open. Or closed. Or starting a revolution.',
        canTalk: false,
        canUse: false,
        onPickUp: () => {
          crowbar.destroy();
          this.hotspots = this.hotspots.filter(h => h.id !== 'crowbar');
        }
      });
    }

    // Stray cat
    const cat = this.add.image(250, 400, 'cat').setDepth(3).setInteractive();
    this.tweens.add({
      targets: cat,
      y: 398,
      duration: 2000,
      yoyo: true,
      repeat: -1
    });
    this.hotspots.push({
      sprite: cat,
      id: 'cat',
      name: 'Stray Cat',
      lookDescription: 'A stray cat with the thousand-yard stare of someone who\'s heard too many open mic nights.',
      canPickUp: false,
      canTalk: true,
      canUse: false
    });

    // Toolbox
    if (!gameState.getFlag('opened_toolbox')) {
      const toolbox = this.add.image(550, 390, 'toolbox').setDepth(3).setInteractive();
      this.hotspots.push({
        sprite: toolbox,
        id: 'toolbox',
        name: 'Toolbox',
        lookDescription: 'Someone left a toolbox out here. Probably the last roadie. They say he\'s still out there somewhere, carrying a particularly heavy amp.',
        canPickUp: false,
        canTalk: false,
        canUse: true,
        useAction: () => {
          gameState.setFlag('opened_toolbox', true);
          return 'Eddie opens the toolbox. Inside: three rusty screwdrivers, a flashlight with dead batteries, and a note that reads "I quit." Relatable.';
        }
      });
    }

    // Poster on the alley wall
    const alleyPoster = this.add.image(150, 200, 'poster').setDepth(2).setInteractive();
    this.hotspots.push({
      sprite: alleyPoster,
      id: 'alley_poster',
      name: 'Torn Poster',
      lookDescription: '"Battle of the Ban—" the rest is torn off. Either "Bands" or "Bananas." Eddie hopes it\'s the first one.',
      canPickUp: false,
      canTalk: false,
      canUse: false
    });

    // Door back to Rusty Amp
    const door = this.add.image(40, 330, 'door').setDepth(3).setInteractive();
    this.hotspots.push({
      sprite: door,
      id: 'rusty_amp_door',
      name: 'Back Door (inside)',
      lookDescription: 'The door back into The Rusty Amp. Somehow the back alley smells better.',
      canPickUp: false,
      canTalk: false,
      canUse: true,
      useAction: () => {
        this.transitionTo('RustyAmpScene');
        return null;
      }
    });

    // Left arrow hint
    const arrow = this.add.image(20, 380, 'arrow_left').setDepth(10).setAlpha(0.5).setInteractive();
    this.tweens.add({
      targets: arrow,
      x: 15,
      duration: 800,
      yoyo: true,
      repeat: -1
    });
    arrow.on('pointerdown', () => {
      this.transitionTo('RustyAmpScene');
    });

    // Add hover highlights
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
    const targetX = Math.max(this.walkableArea.minX, Math.min(this.walkableArea.maxX, hotspot.sprite.x));
    const targetY = Math.max(this.walkableArea.minY, Math.min(this.walkableArea.maxY, hotspot.sprite.y + 30));
    this.pendingAction = { verb, target: hotspot };
    this.walkTo(targetX, targetY);
  }

  performAction(verb: string, hotspot: Hotspot): void {
    switch (verb) {
      case 'look':
        this.showMessage(hotspot.lookDescription);
        break;
      case 'talk':
        if (hotspot.id === 'cat') {
          this.showMessage('Eddie meows at the cat. The cat stares at him with visible contempt. At least someone in this alley has standards.');
        } else if (hotspot.canTalk) {
          this.showMessage('They don\'t seem interested in conversation.');
        } else {
          this.showMessage(`Eddie talks to the ${hotspot.name}. It doesn't talk back. As expected.`);
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
          this.showMessage(`Eddie can't pick that up. Physics won't allow it. Neither would common sense.`);
        }
        break;
      case 'use':
        if (hotspot.canUse && hotspot.useAction) {
          const result = hotspot.useAction();
          if (result) this.showMessage(result);
        } else {
          this.showMessage(`Eddie isn't sure what to do with the ${hotspot.name}. Join the club, ${hotspot.name}.`);
        }
        break;
    }
  }

  walkTo(x: number, y: number): void {
    const targetX = Math.max(this.walkableArea.minX, Math.min(this.walkableArea.maxX, x));
    const targetY = Math.max(this.walkableArea.minY, Math.min(this.walkableArea.maxY, y));
    this.walkTarget = { x: targetX, y: targetY };
    this.isWalking = true;

    if (targetX > this.player.x) {
      this.player.setFlipX(false);
      this.facingRight = true;
    } else {
      this.player.setFlipX(true);
      this.facingRight = false;
    }

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
    gameState.playerPosition = sceneKey === 'RustyAmpScene'
      ? { x: 880, y: 370 }
      : { x: 80, y: 370 };
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

      this.player.setDepth(Math.floor(this.player.y / 10));
      gameState.playerPosition = { x: this.player.x, y: this.player.y };
    }
  }
}
