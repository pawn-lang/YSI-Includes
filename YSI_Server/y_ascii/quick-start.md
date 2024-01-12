# Quick Start

 Introduction
--------------

This library allows you to print fancy text in the console, with borders and correct wrapping.  Text is built up in sections, each separated from the last; with the whole document enclosed in a larger box.

 Example
---------

```pawn
#include <YSI_Server\y_ascii>

main()
{
	// Start a new text display.
	ASCII_StartDisplay(ASCII_BORDER_STYLE_PILLARS);
	// Start a new section.
	ASCII_StartSection(ASCII_BORDER_STYLE_PILLARS);
	// Print some text in the section (left-aligned).
	ASCII_PrintSection("This library allows you to print fancy text in the console, with borders and correct wrapping.  Text is built up in sections, each separated from the last; with the whole document enclosed in a larger box.", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	// End the current section.
	ASCII_EndSection(ASCII_BORDER_STYLE_PILLARS);
	// Start a new section.
	ASCII_StartSection(ASCII_BORDER_STYLE_PILLARS);
	// Print some text in the section (centre-aligned).
	ASCII_PrintSection("This is some example text you don't need to worry about.  Most people would use Lorem-Ipsum for this, since it is basically gibberish with realistic word length distribution.", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_CENTRE);
	// End the current section.
	ASCII_EndSection(ASCII_BORDER_STYLE_PILLARS);
	// Make a bigger gap to the next section.
	ASCII_Separate(ASCII_BORDER_STYLE_PILLARS);
	// Start a new section.
	ASCII_StartSection(ASCII_BORDER_STYLE_PILLARS);
	// Print a lot of text.
	ASCII_PrintSection("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintSection("", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintSection("Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora incidunt ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? Quis autem vel eum iure reprehenderit qui in ea voluptate velit esse quam nihil molestiae consequatur, vel illum qui dolorem eum fugiat quo voluptas nulla pariatur?", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintSection("", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	ASCII_PrintSection("At vero eos et accusamus et iusto odio dignissimos ducimus qui blanditiis praesentium voluptatum deleniti atque corrupti quos dolores et quas molestias excepturi sint occaecati cupiditate non provident, similique sunt in culpa qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio. Nam libero tempore, cum soluta nobis est eligendi optio cumque nihil impedit quo minus id quod maxime placeat facere possimus, omnis voluptas assumenda est, omnis dolor repellendus. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet ut et voluptates repudiandae sint et molestiae non recusandae. Itaque earum rerum hic tenetur a sapiente delectus, ut aut reiciendis voluptatibus maiores alias consequatur aut perferendis doloribus asperiores repellat.", ASCII_BORDER_STYLE_PILLARS, ASCII_ALIGNMENT_STYLE_LEFT);
	// End the current section.
	ASCII_EndSection(ASCII_BORDER_STYLE_PILLARS);
	// End the whole text display.
	ASCII_EndDisplay(ASCII_BORDER_STYLE_PILLARS);
}
```

This example will print:

```
                                    ___---___
                              ___---___---___---___
                        ___---___---    *    ---___---___
                  ___---___---    o/ 0_/  @  o ^   ---___---___
            ___---___--- @  i_e J-U /|  -+D O|-| (o) /   ---___---___
      ___---___---    __/|  //\  /|  |\  /\  |\|  |_  __--oj   ---___---___
 __---___---_________________________________________________________---___---__
 ===============================================================================
  ||||                                                                     ||||
  |---------------------------------------------------------------------------|
  |___-----___-----___-----___-----___-----___-----___-----___-----___-----___|
  / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \
 ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) )
  \__/=====\__/   \__/=====\__/   \__/=====\__/   \__/=====\__/   \__/=====\__/
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)
     J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L
    ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ
   ===========================================================================
  ||||                                                                     ||||
  |---------------------------------------------------------------------------|
  |___-----___-----___-----___-----___-----___-----___-----___-----___-----___|
  / _ \===/ _ \                                                   / _ \===/ _ \
 ( (.\ oOo /.) )                                                 ( (.\ oOo /.) )
  \__/=====\__/                                                   \__/=====\__/
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     ||||||| This library allows you to print fancy text in the con- |||||||
     ||||||| sole, with borders and correct wrapping.  Text is built |||||||
     ||||||| up in sections, each separated from the last; with the  |||||||
     ||||||| whole document enclosed in a larger box.                |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     (oOoOo)                                                         (oOoOo)
     J%%%%%L                                                         J%%%%%L
    ZZZZZZZZZ                                                       ZZZZZZZZZ
   ===========================================================================
  ||||                                                                     ||||
  |---------------------------------------------------------------------------|
  |___-----___-----___-----___-----___-----___-----___-----___-----___-----___|
  / _ \===/ _ \                                                   / _ \===/ _ \
 ( (.\ oOo /.) )                                                 ( (.\ oOo /.) )
  \__/=====\__/                                                   \__/=====\__/
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||    This is some example text you don't need to worry    |||||||
     |||||||   about.  Most people would use Lorem-Ipsum for this,   |||||||
     |||||||   since it is basically gibberish with realistic word   |||||||
     |||||||                  length distribution.                   |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     (oOoOo)                                                         (oOoOo)
     J%%%%%L                                                         J%%%%%L
    ZZZZZZZZZ                                                       ZZZZZZZZZ
   ===========================================================================
  ||||                                                                     ||||
  |---------------------------------------------------------------------------|
  |___-----___-----___-----___-----___-----___-----___-----___-----___-----___|
  / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \
 ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) )
  \__/=====\__/   \__/=====\__/   \__/=====\__/   \__/=====\__/   \__/=====\__/
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)
     J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L
    ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ
   ===========================================================================
  ||||                                                                     ||||
  |---------------------------------------------------------------------------|
  |___-----___-----___-----___-----___-----___-----___-----___-----___-----___|
  / _ \===/ _ \                                                   / _ \===/ _ \
 ( (.\ oOo /.) )                                                 ( (.\ oOo /.) )
  \__/=====\__/                                                   \__/=====\__/
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     ||||||| Lorem ipsum dolor sit amet, consectetur adipiscing      |||||||
     ||||||| elit, sed do eiusmod tempor incididunt ut labore et     |||||||
     ||||||| dolore magna aliqua. Ut enim ad minim veniam, quis nos- |||||||
     ||||||| trud exercitation ullamco laboris nisi ut aliquip ex ea |||||||
     ||||||| commodo consequat. Duis aute irure dolor in reprehende- |||||||
     ||||||| rit in voluptate velit esse cillum dolore eu fugiat     |||||||
     ||||||| nulla pariatur. Excepteur sint occaecat cupidatat non   |||||||
     ||||||| proident, sunt in culpa qui officia deserunt mollit     |||||||
     ||||||| anim id est laborum.                                    |||||||
     |||||||                                                         |||||||
     ||||||| Sed ut perspiciatis unde omnis iste natus error sit     |||||||
     ||||||| voluptatem accusantium doloremque laudantium, totam rem |||||||
     ||||||| aperiam, eaque ipsa quae ab illo inventore veritatis et |||||||
     ||||||| quasi architecto beatae vitae dicta sunt explicabo.     |||||||
     ||||||| Nemo enim ipsam voluptatem quia voluptas sit aspernatur |||||||
     ||||||| aut odit aut fugit, sed quia consequuntur magni dolores |||||||
     ||||||| eos qui ratione voluptatem sequi nesciunt. Neque porro  |||||||
     ||||||| quisquam est, qui dolorem ipsum quia dolor sit amet,    |||||||
     ||||||| consectetur, adipisci velit, sed quia non numquam eius  |||||||
     ||||||| modi tempora incidunt ut labore et dolore magnam aliq-  |||||||
     ||||||| uam quaerat voluptatem. Ut enim ad minima veniam, quis  |||||||
     ||||||| nostrum exercitationem ullam corporis suscipit laborio- |||||||
     ||||||| sam, nisi ut aliquid ex ea commodi consequatur? Quis    |||||||
     ||||||| autem vel eum iure reprehenderit qui in ea voluptate    |||||||
     ||||||| velit esse quam nihil molestiae consequatur, vel illum  |||||||
     ||||||| qui dolorem eum fugiat quo voluptas nulla pariatur?     |||||||
     |||||||                                                         |||||||
     ||||||| At vero eos et accusamus et iusto odio dignissimos duc- |||||||
     ||||||| imus qui blanditiis praesentium voluptatum deleniti     |||||||
     ||||||| atque corrupti quos dolores et quas molestias excepturi |||||||
     ||||||| sint occaecati cupiditate non provident, similique sunt |||||||
     ||||||| in culpa qui officia deserunt mollitia animi, id est    |||||||
     ||||||| laborum et dolorum fuga. Et harum quidem rerum facilis  |||||||
     ||||||| est et expedita distinctio. Nam libero tempore, cum     |||||||
     ||||||| soluta nobis est eligendi optio cumque nihil impedit    |||||||
     ||||||| quo minus id quod maxime placeat facere possimus, omnis |||||||
     ||||||| voluptas assumenda est, omnis dolor repellendus. Tempo- |||||||
     ||||||| ribus autem quibusdam et aut officiis debitis aut rerum |||||||
     ||||||| necessitatibus saepe eveniet ut et voluptates repudian- |||||||
     ||||||| dae sint et molestiae non recusandae. Itaque earum      |||||||
     ||||||| rerum hic tenetur a sapiente delectus, ut aut reicien-  |||||||
     ||||||| dis voluptatibus maiores alias consequatur aut perfere- |||||||
     ||||||| ndis doloribus asperiores repellat.                     |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     |||||||                                                         |||||||
     (oOoOo)                                                         (oOoOo)
     J%%%%%L                                                         J%%%%%L
    ZZZZZZZZZ                                                       ZZZZZZZZZ
   ===========================================================================
  ||||                                                                     ||||
  |---------------------------------------------------------------------------|
  |___-----___-----___-----___-----___-----___-----___-----___-----___-----___|
  / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \   / _ \===/ _ \
 ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) ) ( (.\ oOo /.) )
  \__/=====\__/   \__/=====\__/   \__/=====\__/   \__/=====\__/   \__/=====\__/
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     |||||||         |||||||         |||||||         |||||||         |||||||
     (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)         (oOoOo)
     J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L         J%%%%%L
    ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ       ZZZZZZZZZ
   ===========================================================================
   |_________________________________________________________________________|
  |___________________________________________________________________________|
 |_____________________________________________________________________________|
 _______________________________________________________________________________
```

Notice the line wrapping.  There are other, more boring, border styles.