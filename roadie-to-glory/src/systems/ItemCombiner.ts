import { gameState } from './GameState';

interface CombinationResult {
  resultId: string;
  resultName: string;
  resultDescription: string;
  removeA: boolean;
  removeB: boolean;
  message: string;
}

const combinations: Record<string, CombinationResult> = {
  'duct_tape+mic_cable': {
    resultId: 'working_mic',
    resultName: 'Working Microphone',
    resultDescription: 'A microphone held together by duct tape and sheer willpower.',
    removeA: true,
    removeB: true,
    message: 'Eddie wraps the cable with duct tape. It\'s ugly, but it works.'
  },
  'crowbar+guitar_string': {
    resultId: 'improvised_tool',
    resultName: 'Improvised Tool',
    resultDescription: 'A crowbar with a guitar string tied to it. MacGyver would be proud. Or horrified.',
    removeA: false,
    removeB: true,
    message: 'Eddie ties the guitar string to the crowbar. He\'s not sure why, but it feels right.'
  }
};

function makeKey(idA: string, idB: string): string {
  return [idA, idB].sort().join('+');
}

export interface CombineResponse {
  success: boolean;
  message: string;
  item?: { id: string; name: string };
}

export class ItemCombiner {
  static canCombine(idA: string, idB: string): boolean {
    const key = makeKey(idA, idB);
    return key in combinations;
  }

  static combine(idA: string, idB: string): CombineResponse {
    const key = makeKey(idA, idB);
    const combo = combinations[key];
    if (!combo) {
      return {
        success: false,
        message: 'Those two things don\'t go together. Though honestly, neither does anything in Eddie\'s life.'
      };
    }

    if (combo.removeA) gameState.removeItem(idA);
    if (combo.removeB) gameState.removeItem(idB);
    gameState.addItem({
      id: combo.resultId,
      name: combo.resultName,
      description: combo.resultDescription
    });

    return {
      success: true,
      message: combo.message,
      item: { id: combo.resultId, name: combo.resultName }
    };
  }
}
