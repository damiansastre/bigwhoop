// World Interactions
// Generic "look at" and "use" fallback dialogues for world objects.
// Short, witty one-liners. Eddie's inner monologue as he interacts with the venue.

VAR interaction_type = "look"

{ interaction_type:
    - "look": -> look_fallbacks
    - "use": -> use_fallbacks
    - "pickup": -> pickup_fallbacks
    - "talk": -> talk_fallbacks
    - else: -> look_fallbacks
}

=== look_fallbacks ===
Eddie squints at it. It doesn't squint back. Small mercies.
-> END

=== use_fallbacks ===
Eddie pokes at it experimentally. Nothing happens. This is why he's a roadie and not an engineer.
-> END

=== pickup_fallbacks ===
Eddie reaches for it, then reconsiders. Some things are better left where they are. Like this thing. And Eddie's career.
-> END

=== talk_fallbacks ===
Eddie opens his mouth to talk to it, then remembers it's an inanimate object. He does this more often than he'd like to admit.
-> END

=== look_speaker ===
A speaker so heavy it probably has its own zip code. There's something underneath it, but moving it would require either a lever or significantly more upper body strength than Eddie possesses.
-> END

=== look_mic_stand ===
A mic stand held together by rust and optimism. It leans slightly to the left, like it's tired. Eddie can relate.
-> END

=== look_bar_counter ===
The bar counter has seen things. Done things. Absorbed things. The layers of stickiness tell a story — a gross, unsanitary story, but a story nonetheless.
-> END

=== look_poster ===
A faded poster for a band called "Temporary Deafness." Their tagline: "You'll thank us when it's over."
Eddie isn't sure if that's a threat or a promise.
-> END

=== look_jukebox ===
An ancient jukebox that lists two songs: "Heartbreak Hotel" and something called "DO NOT PLAY."
The "DO NOT PLAY" button has been pressed so many times it's worn smooth.
Nobody knows what the song is. Nobody who's heard it will talk about it.
-> END

=== look_crate ===
A wooden crate full of cables that have achieved sentience through sheer entanglement. Darwin would be fascinated. Eddie is just annoyed.
-> END

=== look_door ===
A door. It leads somewhere else. Specifically, somewhere that isn't here. That's either its best or worst quality, depending on the day.
-> END

=== look_dumpster ===
A dumpster that doubles as a archaeological dig site for broken dreams and discarded setlists. It smells exactly how you'd expect. Actually, it smells worse.
-> END

=== look_cat ===
A stray cat with the confidence of a headliner and the hygiene of a mosh pit. It watches Eddie with the quiet judgment of someone who's made better life choices.
-> END

=== look_toolbox ===
A toolbox. The last bastion of hope for anyone trying to fix anything in this venue. It's red, which is either a design choice or a warning.
-> END

=== look_crowbar ===
A crowbar. Half-Life fans would be excited. Eddie is just cold.
-> END

=== use_jukebox ===
Eddie feeds it a coin. The jukebox makes a sound like a robot having a mid-life crisis, plays three notes of "Stairway to Heaven," then gives up entirely.
Fair enough. Even the jukebox knows some songs are too ambitious for this venue.
-> END

=== use_dumpster ===
Eddie rummages through the dumpster. He finds broken dreams, a mysterious substance, and what might be a guitar pick or a very small tortilla chip.
# give_item: guitar_pick, Guitar Pick, A pick salvaged from a dumpster. Has seen things.
It's a guitar pick. Probably.
-> END

=== use_door ===
Eddie opens the door. On the other side: more venue. It's venues all the way down.
-> END

=== use_mic_stand ===
Eddie grabs the mic stand and poses. For a moment — just a moment — he's a rock star.
Then gravity and self-awareness kick in. The moment passes.
-> END

=== use_broken_thing ===
It's broken. Eddie's not great at fixing things. He's more of a "carry things and set them down slightly to the left" kind of guy.
That's literally his job description. He checked.
-> END

=== talk_to_object ===
Eddie: Hey there, little guy.
The object says nothing. Because it's an object.
Eddie isn't sure what he expected. He IS sure this isn't the weirdest thing he's done today.
-> END

=== talk_to_cat ===
Eddie: Meow?
The cat stares at Eddie with the intensity of a thousand disapproving grandmothers.
Then it licks its paw. Conversation over.
Eddie has been dismissed. By a cat. In an alley. Behind a bar.
This is rock bottom. Or at least rock adjacent.
-> END

=== generic_combine_fail ===
Eddie tries to combine the two items. They don't combine. They're not even compatible. Like pineapple on pizza, but for adventure game inventory items.
Actually, pineapple on pizza at least TASTES like something. This combination tastes like failure.
-> END

=== nothing_happens ===
Nothing happens.
Nothing continues to happen.
Eddie waits.
Still nothing.
This is either a zen moment or a bug. Eddie can't tell. Neither can the developer, probably.
-> END

=== already_done ===
Eddie already did that. Once was enough. Twice would be a pattern. Three times would be a hobby.
Eddie has enough hobbies. Like carrying heavy things and questioning his life choices.
-> END

=== cant_reach ===
Eddie stretches. Strains. Makes a noise that's somewhere between a grunt and a prayer.
Nope. Can't reach it. His arms are too short, the thing is too far, and the laws of physics remain uncooperative.
-> END

=== inventory_full ===
Eddie's pockets are full. His hands are full. His heart is full — wait, no. That last one's just heartburn from the bar's "food."
He needs to use or drop something first.
-> END

=== dark_too_dark ===
It's too dark to see anything. Eddie waves his hands around like a mime having a bad day.
He touches something. He's not sure what. He doesn't want to find out.
-> END
