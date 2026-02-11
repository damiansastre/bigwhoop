// Rick the Barkeep
// Voice: Communicates through grunts and sighs. Occasional world-weary wisdom.
// Short, punchy dialogue. A man who has cleaned too many glasses and seen too many things.

VAR met_rick_before = false
VAR has_working_mic = false
VAR sal_is_mentor = false
VAR knows_about_botb = false

{ met_rick_before:
    -> returning
- else:
    -> first_meeting
}

=== first_meeting ===
# meet_npc: barkeep
~ met_rick_before = true
Rick is polishing a glass. The glass is not getting cleaner. He doesn't seem to care.
Rick: ...
He looks up. Sighs.
Rick: Drink?
+ [I'm Eddie. I'm the new roadie.]
    Rick: Hmm.
    He goes back to polishing the glass.
    Rick: ...roadie. Okay.
    Rick: *sigh*
    -> main_menu
+ [What can you tell me about this place?]
    Rick: *grunt*
    He gestures broadly at the bar. At the stains. At existence.
    Rick: This.
    -> main_menu
+ [Just looking around.]
    Rick: Mm.
    He nods. This constitutes a full conversation by Rick's standards.
    -> main_menu

=== returning ===
Rick looks up. Exhales through his nose. This is his version of "welcome back."
Rick: ...
+ [Hey Rick.]
    Rick: Mm.
    -> main_menu
+ [Still polishing that glass?]
    Rick: ...different glass.
    A pause.
    Rick: Same futility.
    -> main_menu

=== main_menu ===
+ [Know where I can find useful stuff around here?]
    -> find_things
+ [Tell me about the venue's history.]
    -> venue_history
+ [What do you serve here?]
    -> drinks_menu
+ {knows_about_botb} [What do you know about the Battle of the Bands?]
    -> botb_info
+ [See you later, Rick.]
    Rick nods. Barely perceptible. A millimeter at most.
    Rick: Mm.
    -> END

=== find_things ===
Rick: *sigh*
Rick puts down the glass. This is significant. He never puts down the glass.
Rick: Back alley. Stuff out there.
Rick: Crowbar. Junk. Cat.
+ [A crowbar? What for?]
    Rick: Prying.
    A long pause.
    Rick: ...things.
    Rick: Heavy things don't move themselves.
    Rick picks the glass back up. The wisdom dispensary is closed.
    -> main_menu
+ [Anything useful behind the bar?]
    Rick: Duct tape. Counter.
    He points with his chin. Maximum efficiency.
    Rick: Fixes everything.
    Rick: *pause*
    Rick: Almost everything.
    Rick stares into the middle distance. He might be thinking about his marriage. Or the plumbing. Same thing, maybe.
    -> main_menu
+ [What about the cat?]
    Rick: Cat's a cat.
    Rick: Shows up. Leaves. Doesn't pay tab.
    Rick: ...respect that, actually.
    -> main_menu
+ [Thanks.]
    Rick: Mm.
    -> main_menu

=== venue_history ===
Rick puts down the glass again. He clears his throat. This is Rick preparing to give a speech.
Rick: 1974. Speakeasy.
Rick: 1981. Punk venue.
Rick: 1989. Jazz club. Three weeks. Bad idea.
+ [Why was jazz a bad idea?]
    Rick: Smooth jazz night. First and last.
    Rick: Kenny G cover band. Called themselves "Kenny H."
    Rick: Audience rioted. Three saxophones broken. One trombone... missing.
    Rick: We don't talk about the trombone.
    Rick: *long sigh*
    -> venue_history_2
+ [What happened in the '90s?]
    -> venue_history_2
+ [Back to other topics.]
    -> main_menu

=== venue_history_2 ===
Rick: '93. Grunge.
Rick: Band called "Apathy." Fitting.
Rick: Lead singer fell asleep during their own set. Audience thought it was performance art.
Rick: Four-star review in the local paper.
+ [That's amazing.]
    Rick: Mm.
    Rick: '99. Y2K party. Nothing crashed except the drum kit.
    Rick: 2005. Emo phase. Bar went through a lot of black napkins.
    Rick: 2010. Dubstep. I don't want to talk about 2010.
    -> venue_history_3
+ [What about the 2000s?]
    -> venue_history_3
+ [Back to other topics.]
    -> main_menu

=== venue_history_3 ===
Rick: 2015. Venue almost closed.
Rick: Saved by a charity concert. Twelve bands. Forty-seven noise complaints.
Rick: 2020. ...closed. Obviously.
Rick: 2021. Reopened. Cockroaches held the fort.
Rick: Now... *gestures at everything*
Rick: ...this.
+ [You've been here through all of it?]
    Rick: Since '92.
    Rick: Thirty-four years.
    Rick: Three owners. Seven health inspections. Zero passed.
    Rick: ...I've outlasted them all.
    Rick picks up the glass again. Starts polishing. The circle of life.
    -> main_menu
+ [Wow. That's... a lot of history.]
    Rick: History.
    Rick: Or a cautionary tale.
    Rick: Same thing.
    Rick: *shrug*
    -> main_menu

=== drinks_menu ===
Rick: Beer. Warm.
Rick: Whiskey. Questionable.
Rick: Water. ...also questionable.
+ [I'll have a beer.]
    Rick pours a beer. It's flat. It's warm. It's perfect for this venue.
    Rick: Three bucks.
    Rick: ...or a good story. Whichever.
    -> main_menu
+ [What's in the whiskey?]
    Rick: Whiskey.
    Rick: Probably.
    Rick: Label fell off in 2014. We've been guessing since.
    Rick: Regular says it tastes like "regret with a smoky finish."
    Rick: ...put that on the menu.
    -> main_menu
+ [I'll pass.]
    Rick: Smart.
    Rick: ...first smart person I've met in here.
    -> main_menu

=== botb_info ===
Rick: Battle of the Bands.
Rick: *sigh*
Rick: Every year.
Rick: Twelve bands. Twelve dreams. Twelve disappointments.
Rick: ...usually.
+ [Any tips for entering?]
    Rick: Don't.
    A pause.
    Rick: ...but if you do.
    Rick: Be real.
    Rick: Audience smells fake. Like they smell the whiskey.
    Rick: Can't fool either.
    -> main_menu
+ [Who usually wins?]
    Rick: Last year. "Existential Dread."
    Rick: Year before. "The Vacant Stares."
    Rick: Year before that. "My Landlord's Band."
    Rick: ...they were actually the landlord's band. He owned the venue then.
    Rick: Conflict of interest. Nobody cared.
    -> main_menu
+ [Back to other topics.]
    -> main_menu
