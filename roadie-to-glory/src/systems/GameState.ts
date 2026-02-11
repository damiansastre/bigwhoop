export interface InventoryItem {
  id: string;
  name: string;
  description: string;
}

export interface GameStateData {
  inventory: InventoryItem[];
  flags: Record<string, boolean | string | number>;
  npcsmet: Record<string, boolean>;
  puzzlesSolved: Record<string, boolean>;
  currentScene: string;
  playerPosition: { x: number; y: number };
}

/**
 * Central game state manager.
 * Tracks inventory, quest flags, NPCs met, puzzles solved, and current scene.
 * Decoupled from rendering — can be tested independently.
 */
export class GameState {
  inventory: InventoryItem[] = [];
  flags: Record<string, boolean | string | number> = {};
  npcsmet: Record<string, boolean> = {};
  puzzlesSolved: Record<string, boolean> = {};
  currentScene: string = 'RustyAmpScene';
  playerPosition: { x: number; y: number } = { x: 480, y: 350 };
  currentVerb: string = 'look';
  selectedItem: InventoryItem | null = null;

  constructor() {
    this.reset();
  }

  reset(): void {
    this.inventory = [];
    this.flags = {};
    this.npcsmet = {};
    this.puzzlesSolved = {};
    this.currentScene = 'RustyAmpScene';
    this.playerPosition = { x: 480, y: 350 };
    this.currentVerb = 'look';
    this.selectedItem = null;
  }

  // Inventory
  addItem(item: InventoryItem): boolean {
    if (!this.hasItem(item.id)) {
      this.inventory.push(item);
      return true;
    }
    return false;
  }

  removeItem(id: string): void {
    this.inventory = this.inventory.filter(item => item.id !== id);
  }

  hasItem(id: string): boolean {
    return this.inventory.some(item => item.id === id);
  }

  getItem(id: string): InventoryItem | undefined {
    return this.inventory.find(item => item.id === id);
  }

  // Flags
  setFlag(key: string, value: boolean | string | number = true): void {
    this.flags[key] = value;
  }

  getFlag(key: string): boolean | string | number {
    return this.flags[key] ?? false;
  }

  // Counter flags
  incrementCounter(key: string, amount: number = 1): number {
    if (typeof this.flags[key] !== 'number') {
      this.flags[key] = 0;
    }
    (this.flags[key] as number) += amount;
    return this.flags[key] as number;
  }

  getCounter(key: string): number {
    return typeof this.flags[key] === 'number' ? this.flags[key] as number : 0;
  }

  // NPCs
  meetNPC(name: string): void {
    this.npcsmet[name] = true;
  }

  hasMetNPC(name: string): boolean {
    return this.npcsmet[name] || false;
  }

  // Puzzles
  solvePuzzle(id: string): void {
    this.puzzlesSolved[id] = true;
  }

  isPuzzleSolved(id: string): boolean {
    return this.puzzlesSolved[id] || false;
  }

  // Serialization
  serialize(): string {
    return JSON.stringify({
      inventory: this.inventory,
      flags: this.flags,
      npcsmet: this.npcsmet,
      puzzlesSolved: this.puzzlesSolved,
      currentScene: this.currentScene,
      playerPosition: this.playerPosition
    } as GameStateData);
  }

  deserialize(json: string): void {
    const data: GameStateData = JSON.parse(json);
    this.inventory = data.inventory || [];
    this.flags = data.flags || {};
    this.npcsmet = data.npcsmet || {};
    this.puzzlesSolved = data.puzzlesSolved || {};
    this.currentScene = data.currentScene || 'RustyAmpScene';
    this.playerPosition = data.playerPosition || { x: 480, y: 350 };
  }
}

// Singleton instance
export const gameState = new GameState();
