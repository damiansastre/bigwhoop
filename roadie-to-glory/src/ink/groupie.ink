// Val the Superfan
// Voice: Overly enthusiastic about music. Has been waiting for "the next big thing"
// for 15 years. Endearing, funny, genuinely believes in the magic of live music.
// Gives hints about Battle of the Bands. Joke paths about bands she's seen.

VAR met_val_before = false
VAR sang_for_sal = false
VAR has_working_mic = false
VAR knows_about_botb = false
VAR sal_is_mentor = false

{ met_val_before:
    -> returning
- else:
    -> first_meeting
}

=== first_meeting ===
# meet_npc: groupie
~ met_val_before = true
A woman in a vintage band tee — the band name is so faded it could be anything from "Led Zeppelin" to "Led Zeppole" — bounces up to Eddie.
Val: OH MY GOD. A NEW FACE. DO YOU KNOW HOW LONG IT'S BEEN SINCE THERE'S BEEN A NEW FACE?
Val: I mean, not counting the health inspector. He was new. He was also horrified. But NEW.
+ [Uh... hi. I'm Eddie.]
    Val: EDDIE! That's such a rock star name! Well, it's kind of a mechanic name too, but also ROCK STAR.
    Val: I'm Val. I'm the number one fan of The Rusty Amp. Also the ONLY fan of The Rusty Amp. So, number one by default!
    Val: Still counts!
    -> main_menu
+ [You seem... enthusiastic.]
    Val: I prefer "passionately invested in the underground music ecosystem."
    Val: But yeah, enthusiastic works too!
    Val: I've been coming here for fifteen years waiting for the next big thing.
    Val: Any day now. ANY DAY.
    -> main_menu
+ [Is that a Led Zeppelin shirt?]
    Val: It's actually "Led Zeppole." They were a Led Zeppelin tribute band that also sold Italian pastries.
    Val: They broke up in 2014. Creative differences. Also the fryer caught fire.
    Val: But their acoustic set? *chef's kiss* And their zeppole? Also *chef's kiss*. Literally.
    -> main_menu

=== returning ===
Val spots Eddie and lights up like a Marshall stack at full power.
Val: EDDIE! You're back! I was just telling that stain on the wall about you.
Val: The stain is a great listener. Very judgmental though. It's been there since the '90s so it has opinions.
{ sang_for_sal:
    Val: Wait wait wait. I HEARD you earlier. Through the wall. Or the vents. Or possibly my imagination. BUT IT WAS AMAZING.
    -> post_singing
- else:
    -> main_menu
}

=== post_singing ===
Val: You have IT, Eddie. The thing. The spark. The je ne sais quoi.
Val: I've been waiting fifteen years for someone with the thing!
Val: The last person with "the thing" was a guy named Derek who turned out to be a very talented pigeon.
Val: Long story. Sad ending. He flew away.
+ [Thanks, Val. That means a lot.]
    Val: It SHOULD mean a lot! I have VERY high standards!
    Val: I once booed a band for seven minutes straight. They thought it was applause. They did an encore.
    Val: I booed that too.
    -> main_menu
+ [Are you sure it wasn't the vents?]
    Val: Eddie. I have been to four hundred and seventy-two live shows in this venue.
    Val: I know what the vents sound like. I know what the pipes sound like. I know what the building settling sounds like.
    Val: I've catalogued every non-musical sound this building makes. There are forty-seven of them.
    Val: What I heard was not number forty-seven. What I heard was MUSIC.
    -> main_menu

=== main_menu ===
+ [Tell me about bands you've seen here.]
    -> bands_seen
+ [Got any tips for the Battle of the Bands?]
    -> botb_tips
+ {knows_about_botb} [What's the secret to winning?]
    -> winning_secret
+ [What keeps you coming back here?]
    -> why_here
+ [Gotta go, Val.]
    Val: Go forth and ROCK, Eddie!
    Val: Or at least go forth and don't trip on the cables! There are SO many cables.
    Val: I've counted. There are seventy-three. Four of them aren't connected to anything. Three of them might be snakes.
    -> END

=== bands_seen ===
Val: Oh! OH! You want to hear about the bands? I keep a journal! Volume 23!
Val: Where do I even START?
+ [Start with the best.]
    Val: Best band that ever played here? "Thunderfoot and the Anxiety."
    Val: Lead singer had stage fright. Like, ACTUAL stage fright. She performed from behind the speaker stack.
    Val: Nobody could see her. But her VOICE? It filled this entire room.
    Val: She's a dental hygienist now. But sometimes, when you're getting your teeth cleaned, she hums a few bars of their hit song.
    Val: It's called "Molar Eclipse of the Heart."
    Val: I'm not making that up. I am incapable of making things up. I'm too earnest.
    -> bands_seen_more
+ [Start with the worst.]
    Val: Worst band? Oh, that's easy.
    Val: "The Nickelback Nickelbacks." They were a Nickelback cover band that only played the songs even Nickelback wouldn't play anymore.
    Val: Their set lasted eleven minutes. The psychological damage lasted much longer.
    Val: The lead guitarist is now a motivational speaker. His main topic is "knowing when to stop."
    -> bands_seen_more
+ [Start with the weirdest.]
    Val: "The Interpretive Screamers." They combined interpretive dance with... screaming.
    Val: It was either brilliant performance art or a cry for help. The audience wasn't sure. THEY weren't sure.
    Val: Their encore involved a leaf blower and a wedding dress. I still think about it.
    Val: The fire marshal still thinks about it too. He sends them a card every year. "Please don't come back."
    -> bands_seen_more
+ [Back to other topics.]
    -> main_menu

=== bands_seen_more ===
+ [Any other memorable ones?]
    Val: "Quiet Riot Librarians." All librarians. Played exclusively at whisper volume.
    Val: The audience had to lean in. It was actually really intimate and beautiful.
    Val: Until someone's phone went off and they all shushed the entire venue. IN UNISON.
    Val: Scariest thing I've ever witnessed.
    + + [I love this place.]
        Val: RIGHT?! It's like a zoo but for musicians! And the enclosures are terrible!
        -> main_menu
    + + [How is this venue still open?]
        Val: Spite. Mostly spite. And a VERY flexible definition of "building code."
        -> main_menu
+ [Back to other topics.]
    -> main_menu

=== botb_tips ===
Val: Tips? TIPS? I have been watching this competition for TWELVE YEARS.
Val: I have a SPREADSHEET. I have STATISTICS. I have a HEAT MAP of audience engagement patterns!
+ [That's... thorough.]
    Val: Here's what I know:
    Val: One — the judges care about AUTHENTICITY. Play from the heart. Or the spleen. Wherever your music lives.
    Val: Two — you need a working mic. Last year someone tried to perform without one. The judges thought it was mime.
    Val: They scored it as mime. He got third place in the mime category. There IS no mime category.
    # set_flag: knows_about_botb
    -> botb_tips_more
+ [A heat map? Really?]
    Val: Color-coded by year! Red is "standing ovation." Blue is "confused silence." Gray is "venue evacuation."
    Val: There's been a LOT of gray.
    Val: The sweet spot is right between red and blue. That's where the magic happens.
    Val: It's orange. The magic is orange. I've done the math.
    # set_flag: knows_about_botb
    -> botb_tips_more
+ [Just the basics, please.]
    Val: Get a mic. Get a song. Get on stage. Don't set anything on fire.
    Val: That last one is less obvious than you'd think.
    # set_flag: knows_about_botb
    -> botb_tips_more

=== botb_tips_more ===
+ [What about getting a mentor?]
    Val: OH. OH OH OH. You need SAL.
    Val: Sal knows this venue like I know band trivia. Which is to say EXTREMELY WELL.
    Val: He won't admit it but he used to play. Bassist. In a band called "The Reluctant Participants."
    Val: Perfect name, in retrospect.
    Val: Get him to listen to you play. If he doesn't walk away, you've got a shot!
    -> main_menu
+ [What's the prize?]
    Val: Hundred bucks. Gift card. BUT ALSO.
    Val: A slot at the Thunderdome Festival! That's where the industry people are!
    Val: Real managers! Real labels! People who've heard of HEALTH INSURANCE!
    Val: This is THE shot, Eddie. THE big break. THE moment. THE... the.
    Val: I ran out of "THE"s. You get the idea.
    -> main_menu
+ [Back to other topics.]
    -> main_menu

=== winning_secret ===
Val leans in conspiratorially. She looks both ways. There's nobody else around, but she checks anyway.
Val: Okay. THE secret. The REAL secret.
Val: I've studied twelve years of Battle of the Bands winners.
Val: You know what they all have in common?
+ [What?]
    Val: They all told a STORY. Not just a song. A STORY.
    Val: The audience at The Rusty Amp? They've heard everything. Every genre. Every gimmick.
    Val: But a real story? With heart? That still gets them every time.
    Val: Because under all the irony and the sticky floors and the questionable plumbing...
    Val: Everyone in this room came here because they BELIEVE in something.
    Val: Even if what they believe in is just... this weird, beautiful, terrible place.
    Val gets a little misty-eyed.
    Val: ...sorry. I have a lot of feelings about acoustics.
    -> main_menu
+ [Bribery?]
    Val: WHAT? No! Well... one year, yes. But he was disqualified.
    Val: He tried to bribe the judges with a gift basket. The gift basket was just more of the questionable whiskey from the bar.
    Val: The judges were insulted. Not by the bribery. By the whiskey.
    -> main_menu

=== why_here ===
Val: You know... people ask me that a lot. Usually while backing away slowly.
Val: I was seventeen when I first came to The Rusty Amp. Snuck in with a fake ID.
Val: The bouncer didn't check. There IS no bouncer. There never was.
Val: But I heard this band — "The Midnight Somethings" — and they were... incandescent.
Val: They played for nine people. Five of those people were each other.
Val: But they played like it was Madison Square Garden. Like every note MATTERED.
+ [What happened to them?]
    Val: They broke up. Of course they broke up. Everyone breaks up.
    Val: But for forty-five minutes on a Tuesday night in 2011... they were the best band in the world.
    Val: And I was there. And that was enough.
    Val: That's why I keep coming back. Because what if it happens again?
    Val: What if the NEXT Tuesday night is the one?
    Val: What if it's YOU, Eddie?
    -> main_menu
+ [That's actually really beautiful.]
    Val: I KNOW! I'm very moving! I should charge for these monologues!
    Val: "Val's Inspirational Speeches: $5. Or a band sticker. I accept band stickers."
    -> main_menu
+ [You've been coming here since 2011?]
    Val: Fifteen years. Seven hundred and eighty Tuesdays. Give or take.
    Val: I've only missed three. Two for flu. One for jury duty.
    Val: I tried to get the trial moved to Tuesdays. Judge said no. NO APPRECIATION for live music in the judicial system.
    -> main_menu
