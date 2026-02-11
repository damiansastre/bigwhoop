import { gameState } from './GameState';

interface PuzzleDefinition {
  description: string;
  check: () => boolean;
  solve: () => string;
}

const puzzleDefinitions: Record<string, PuzzleDefinition> = {
  move_speaker: {
    description: 'Move the speaker to get the Battle of the Bands flyer',
    check: () => gameState.hasItem('crowbar'),
    solve: () => {
      gameState.solvePuzzle('move_speaker');
      gameState.addItem({
        id: 'botb_flyer',
        name: 'Battle of the Bands Flyer',
        description: 'A crumpled flyer for the upcoming Battle of the Bands. "72 hours. One stage. No mercy."'
      });
      gameState.removeItem('crowbar');
      return 'Eddie wedges the crowbar under the speaker and heaves. The speaker slides with a horrible screech, revealing a crumpled flyer underneath.';
    }
  },
  fix_mic: {
    description: 'Fix the broken microphone',
    check: () => gameState.hasItem('duct_tape') && gameState.hasItem('mic_cable'),
    solve: () => {
      gameState.solvePuzzle('fix_mic');
      gameState.removeItem('duct_tape');
      gameState.removeItem('mic_cable');
      gameState.addItem({
        id: 'working_mic',
        name: 'Working Microphone',
        description: 'A microphone held together by duct tape and sheer willpower. Like most things in this venue.'
      });
      return 'Eddie wraps the cable with duct tape and reconnects it. The mic crackles to life. It\'s not pretty, but it works — story of Eddie\'s life.';
    }
  },
  convince_sal: {
    description: 'Convince Sal to be your mentor',
    check: () => gameState.hasItem('working_mic') && gameState.getFlag('sang_for_sal') === true,
    solve: () => {
      gameState.solvePuzzle('convince_sal');
      gameState.setFlag('sal_is_mentor', true);
      return 'Sal stares at Eddie for a long moment. "Kid... that was either the best or worst thing I\'ve ever heard. Either way, I\'m in."';
    }
  }
};

export class PuzzleSystem {
  static canSolve(puzzleId: string): boolean {
    const puzzle = puzzleDefinitions[puzzleId];
    if (!puzzle) return false;
    if (gameState.isPuzzleSolved(puzzleId)) return false;
    return puzzle.check();
  }

  static solve(puzzleId: string): string | null {
    const puzzle = puzzleDefinitions[puzzleId];
    if (!puzzle) return null;
    if (gameState.isPuzzleSolved(puzzleId)) return null;
    if (!puzzle.check()) return null;
    return puzzle.solve();
  }

  static getPuzzleDescription(puzzleId: string): string | null {
    const puzzle = puzzleDefinitions[puzzleId];
    return puzzle ? puzzle.description : null;
  }

  static getAvailablePuzzles(): string[] {
    return Object.keys(puzzleDefinitions).filter(id =>
      !gameState.isPuzzleSolved(id) && puzzleDefinitions[id].check()
    );
  }
}
