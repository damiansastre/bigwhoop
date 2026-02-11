// Sal - The Grizzled Sound Guy
// Voice: Gruff, short sentences, reluctant wisdom. A man who's seen too many bands
// and heard too many frequencies that don't exist.

VAR sang_for_sal = false
VAR has_working_mic = false
VAR sal_is_mentor = false
VAR met_sal_before = false

{ met_sal_before:
    -> returning
- else:
    -> first_meeting
}

=== first_meeting ===
# meet_npc: sal
~ met_sal_before = true
Sal doesn't look up. He's adjusting a knob on a mixing board that might be older than democracy.
Sal: Another one. Great.
Sal: You're either lost or desperate. Both, probably.
+ [I'm Eddie. I'm the new roadie.]
    Sal: Roadie. Right.
    Sal: Last roadie quit after three hours. Said something about "the voices in the speakers."
    Sal: They're just feedback. Probably.
    -> main_menu
+ [This place is... something.]
    Sal: "Something." That's diplomatic.
    Sal: The Rusty Amp's been here since '74. Outlasted disco, grunge, and good taste.
    Sal: I've been here since '89. Outlasted my marriage, my hairline, and my faith in humanity.
    -> main_menu
+ [What's that smell?]
    Sal: Character.
    Sal: Also mold. Mostly mold.
    -> main_menu

=== returning ===
Sal glances up from the mixing board. That counts as a warm greeting from him.
Sal: You again.
{ sang_for_sal:
    { sal_is_mentor == false:
        Sal: ...you know, that thing you did earlier with the mic.
        Sal: I've heard a lot of sounds in forty years. Most of them bad.
        Sal: That wasn't bad.
        -> mentor_offer
    - else:
        Sal: Kid. What now.
        -> main_menu
    }
- else:
    Sal: Kid. What now.
    -> main_menu
}

=== main_menu ===
+ [Tell me about this place.]
    -> about_venue
+ [What's the Battle of the Bands?]
    -> battle_of_bands
+ [What happened to your hearing?]
    -> hearing_loss
+ {has_working_mic && not sang_for_sal} [I fixed a mic. Want to hear me play?]
    -> sing_for_sal
+ {sang_for_sal && not sal_is_mentor} [So... will you help me?]
    -> mentor_offer
+ [I should go.]
    Sal: Yep.
    Sal: Don't touch the red cable. Or the blue one. Actually, don't touch anything.
    -> END

=== about_venue ===
Sal: The Rusty Amp. Where careers come to die and cockroaches come to thrive.
Sal: Used to be a speakeasy. Then a jazz club. Then a punk venue. Then a storage unit.
Sal: Now it's all of those things at once, except the jazz club part.
+ [Who owns it?]
    Sal: Officially? A holding company in Delaware.
    Sal: Practically? The rats. They've been here longer. Squatter's rights.
    -> main_menu
+ [Any famous bands play here?]
    Sal: Define "famous."
    Sal: Nirvana was supposed to play here in '91. They walked in, walked out, and played the bar down the street instead.
    Sal: We DID have a guy who opened for a band that once opened for a band that opened for The Ramones.
    Sal: We put that on the marquee for three years.
    -> main_menu
+ [Back to other topics.]
    -> main_menu

=== battle_of_bands ===
Sal: Battle of the Bands. Annual tradition.
Sal: Twelve bands enter. One band wins. The audience loses either way.
+ [How do I enter?]
    Sal: You need three things, kid.
    Sal: A working mic. A song. And a complete disregard for your own dignity.
    Sal: ...so you're two-thirds of the way there already.
    # set_flag: knows_about_botb
    -> main_menu
+ [Who won last year?]
    Sal: Band called "Existential Dread."
    Sal: They played one note for forty-five minutes. The judges were too confused to score anyone else.
    Sal: Avant-garde. Or a broken amp. Nobody's sure.
    -> main_menu
+ [Is it worth entering?]
    Sal: Kid, the prize is a hundred bucks and a gift certificate to Guitar Center.
    Sal: But the winner gets a slot at the Thunderdome Festival.
    Sal: That's where the real scouts show up. Record labels. Managers. People with dental insurance.
    # set_flag: knows_about_thunderdome
    -> main_menu
+ [Back to other topics.]
    -> main_menu

=== hearing_loss ===
Sal: What?
+ [Your hearing. What happened to it?]
    Sal: Forty years of standing next to Marshall stacks, kid. That's what happened.
    Sal: I can't hear anything below 2,000 hertz anymore.
    Sal: On the bright side, I can't hear most of what people say to me.
    Sal: On the other bright side, most of what people say to me isn't worth hearing.
    + + [That's... kind of sad.]
        Sal: Sad? Nah.
        Sal: You know what's sad? I can still hear the ringing. Twenty-four hours a day. Since 1997.
        Sal: It's in the key of B-flat. I checked.
        Sal: We've reached an understanding, the ringing and me. It's the longest relationship I've ever had.
        -> main_menu
    + + [Do you wear earplugs now?]
        Sal: Now he asks.
        Sal: Yeah. Custom-molded. Cost me three hundred bucks.
        Sal: You know what would have cost me zero dollars? Wearing the free ones I was offered in 1983.
        Sal: Let that be a lesson, kid. The free earplugs are never free. They're an investment.
        -> main_menu
    + + [Can you hear me right now?]
        Sal: I can see your lips moving and I've gotten very good at guessing.
        Sal: Fifty percent of the time, I know exactly what someone said.
        Sal: The other fifty percent, I just nod and hope they didn't ask me a question.
        Sal: ...you didn't ask me a question, did you?
        -> main_menu
+ [Never mind.]
    Sal: WHAT?
    Sal: ...sorry. Force of habit.
    -> main_menu

=== sing_for_sal ===
Sal: You want to play. For me. On purpose.
Sal: Kid, I've heard things in this venue that would make a dog howl.
Sal: Things that violated the Geneva Convention.
Sal: ...but sure. Go ahead. What's the worst that could happen?
Sal squints and adjusts his hearing aid. This is the closest thing to enthusiasm he's displayed since 1994.
~ sang_for_sal = true
# set_flag: sang_for_sal
# play_anim: eddie_sing
Eddie steps up to the mic stand. Clears his throat. And plays.
The sound that comes out is raw. Rough around the edges. But there's something there.
Something real.
Sal's eyebrows move approximately two millimeters upward. For Sal, this is a standing ovation.
Sal: ...
Sal: Huh.
+ [So? What did you think?]
    Sal: I've heard worse.
    Sal: That's the nicest thing I've said to anyone in this building since 2008.
    -> mentor_offer
+ [*waits nervously*]
    Sal stares for what feels like an hour. It's actually twelve seconds.
    Sal: You're not terrible.
    Sal: And in this venue, "not terrible" puts you in the top one percent.
    -> mentor_offer

=== mentor_offer ===
Sal: Look, kid. I don't do this. I don't "mentor." I don't "inspire."
Sal: I stand behind a mixing board and make sure the feedback doesn't kill anyone.
+ [But you know everything about this business.]
    Sal: I know everything about making things louder. That's not the same thing.
    Sal: ...
    Sal: But I guess I know a few other things too.
    -> sal_agrees
+ [I need help entering the Battle of the Bands.]
    Sal: The Battle of the Bands. You're serious.
    Sal: ...
    Sal: Yeah, alright. Somebody's gotta make sure you don't embarrass yourself up there.
    Sal: More than usual, I mean.
    -> sal_agrees
+ [Forget it. I'll figure it out alone.]
    Sal: ...
    Sal: Kid. Wait.
    Sal: I've watched a hundred wannabes walk through that door. Most of them walked right back out.
    Sal: You're still here. That's either stupid or brave. Same thing, usually.
    -> sal_agrees

=== sal_agrees ===
Sal takes off his headphones. He hasn't done that in six years.
Sal: Alright. Here's the deal.
Sal: I'll help you get stage-ready for the Battle of the Bands.
Sal: But you do exactly what I say. No arguments. No "creative differences."
Sal: I've had enough creative differences to last me a lifetime. I'm still paying alimony from the last one.
~ sal_is_mentor = true
# set_flag: sal_is_mentor
# solve_puzzle: convince_sal
Sal: First thing. You need to find the Battle of the Bands flyer. Entry form's on the back.
Sal: There's one around here somewhere. Under one of those speakers, I think.
Sal: Good luck moving it. That thing weighs more than my regrets, and that's saying something.
-> END
