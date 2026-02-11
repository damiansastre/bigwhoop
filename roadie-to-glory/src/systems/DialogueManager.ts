import { Story } from 'inkjs';
import { gameState, InventoryItem } from './GameState';

export interface DialogueLine {
  text: string;
  tags: string[];
}

export interface DialogueChoice {
  text: string;
  index: number;
}

export interface DialogueResult {
  lines: DialogueLine[];
  choices: DialogueChoice[];
  tags: string[];
}

/**
 * Manages ink story loading and state, bridging inkjs with the game.
 * Handles tag parsing to trigger game events (give_item, set_flag, play_anim, etc).
 */
export class DialogueManager {
  private stories: Record<string, object> = {};
  private activeStory: Story | null = null;
  private activeStoryId: string | null = null;
  private _animCallback: ((anim: string) => void) | null = null;
  private _sceneCallback: ((scene: string) => void) | null = null;

  loadStory(id: string, jsonContent: object): void {
    this.stories[id] = jsonContent;
  }

  startStory(id: string): DialogueResult | null {
    if (!this.stories[id]) {
      console.error(`Story '${id}' not loaded`);
      return null;
    }
    this.activeStory = new Story(this.stories[id] as any);
    this.activeStoryId = id;
    this.syncGameStateToInk();
    return this.continue();
  }

  syncGameStateToInk(): void {
    if (!this.activeStory) return;
    for (const [key, value] of Object.entries(gameState.flags)) {
      try {
        (this.activeStory.variablesState as any).$(key, value);
      } catch (_e) {
        // Variable doesn't exist in this story, that's fine
      }
    }
    for (const item of gameState.inventory) {
      try {
        (this.activeStory.variablesState as any).$('has_' + item.id, true);
      } catch (_e) {
        // Variable doesn't exist in this story
      }
    }
  }

  continue(): DialogueResult | null {
    if (!this.activeStory) return null;

    const lines: DialogueLine[] = [];
    const tags: string[] = [];

    while (this.activeStory.canContinue) {
      const text = (this.activeStory.Continue() || '').trim();
      const currentTags: string[] = this.activeStory.currentTags || [];

      if (text) {
        lines.push({ text, tags: [...currentTags] });
      }

      for (const tag of currentTags) {
        this.processTag(tag);
        tags.push(tag);
      }
    }

    const choices: DialogueChoice[] = this.activeStory.currentChoices.map((choice) => ({
      text: choice.text,
      index: choice.index
    }));

    return { lines, choices, tags };
  }

  chooseChoice(index: number): DialogueResult | null {
    if (!this.activeStory) return null;
    this.activeStory.ChooseChoiceIndex(index);
    return this.continue();
  }

  processTag(tag: string): void {
    const parts = tag.split(':').map(s => s.trim());
    const command = parts[0];
    const args = parts.slice(1).join(':').trim();

    switch (command) {
      case 'give_item': {
        const [id, name, description] = args.split(',').map(s => s.trim());
        const item: InventoryItem = { id, name, description: description || name };
        gameState.addItem(item);
        break;
      }
      case 'remove_item': {
        gameState.removeItem(args);
        break;
      }
      case 'set_flag': {
        const [flag, value] = args.split(',').map(s => s.trim());
        gameState.setFlag(flag, value === 'false' ? false : value || true);
        break;
      }
      case 'meet_npc': {
        gameState.meetNPC(args);
        break;
      }
      case 'solve_puzzle': {
        gameState.solvePuzzle(args);
        break;
      }
      case 'play_anim': {
        if (this._animCallback) {
          this._animCallback(args);
        }
        break;
      }
      case 'change_scene': {
        if (this._sceneCallback) {
          this._sceneCallback(args);
        }
        break;
      }
    }
  }

  onAnim(callback: (anim: string) => void): void {
    this._animCallback = callback;
  }

  onSceneChange(callback: (scene: string) => void): void {
    this._sceneCallback = callback;
  }

  getStoryState(): string | null {
    if (!this.activeStory) return null;
    return this.activeStory.state.toJson();
  }

  restoreStoryState(id: string, stateJson: string): boolean {
    if (!this.stories[id]) return false;
    this.activeStory = new Story(this.stories[id] as any);
    this.activeStoryId = id;
    this.activeStory.state.LoadJson(stateJson);
    return true;
  }

  endDialogue(): void {
    this.activeStory = null;
    this.activeStoryId = null;
  }

  isActive(): boolean {
    return this.activeStory !== null;
  }
}

export const dialogueManager = new DialogueManager();
