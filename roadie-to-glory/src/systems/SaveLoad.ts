import { gameState } from './GameState';

const SAVE_KEY = 'roadie-to-glory-save';

interface SaveData {
  gameState: string;
  inkState: string | null;
  timestamp: number;
}

export class SaveLoadSystem {
  static save(inkStoryState?: string | null): boolean {
    const saveData: SaveData = {
      gameState: gameState.serialize(),
      inkState: inkStoryState || null,
      timestamp: Date.now()
    };
    localStorage.setItem(SAVE_KEY, JSON.stringify(saveData));
    return true;
  }

  static load(): SaveData | null {
    const raw = localStorage.getItem(SAVE_KEY);
    if (!raw) return null;
    try {
      const saveData: SaveData = JSON.parse(raw);
      gameState.deserialize(saveData.gameState);
      return saveData;
    } catch (e) {
      console.error('Failed to load save:', e);
      return null;
    }
  }

  static hasSave(): boolean {
    return localStorage.getItem(SAVE_KEY) !== null;
  }

  static deleteSave(): void {
    localStorage.removeItem(SAVE_KEY);
  }
}
