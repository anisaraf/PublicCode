 #!/usr/bin/env perl
use strict;
use warnings;

my $usage = "perl <filename>";
my $filename = shift || die $usage;
my $concordance = {};

open(my $fh, "<", $filename) || die "cannot open $filename $!";
my $currSentence = 0;

while(<$fh>) {
    my @sentences = split_sentences($_);
    foreach my $sentence (@sentences){
	$currSentence++;
	my @words = split_words($sentence);
	foreach my $word (@words) {
	    next if($word eq '');
	    if (defined $concordance->{$word}) {
	        push(@{$concordance->{$word}} , ",$currSentence");
		$concordance->{$word}->[0] = $concordance->{$word}->[0] + 1;  
	    } else {
		$concordance->{$word} = [1,":",$currSentence];
	    }
	}
    }
}

foreach (sort keys(%$concordance) )
{
    print "$_ {@{ $concordance->{$_} }}\n"
}

sub split_sentences
{
    my @PUNCTUATION = ( '\.', '\!', '\?' );
    my $text = shift;

    return () unless $text;

    # capital letter is a character set; to account for local, this includes
    # all characters for which lc is different from that character

    my $capital_letter =  
        '[' . 
            join( '', 
                grep { lc( $_ ) ne ( $_ ) } 
                map { chr( $_ ) } ord( "A" ) .. ord( "\xff" )
            ) . 
        ']'
    ;

    my $punctuation = '(?:' . join( '|', @PUNCTUATION ) . ')';

    # this needs to be alternation, not character class, because of
    # multibyte characters

    my $opt_start_quote = q/['"]?/; # "'
    my $opt_close_quote = q/['"]?/; # "'

    # these are distinguished because (eventually!) I would like to do
    # locale stuff on quote characters

    my $opt_start_bracket = q/[[({]?/; # }{
    my $opt_close_bracket = q/[\])}]?/;

    # return $text if there is no punctuation ...

    return $text unless $text =~ /$punctuation/;

    my @sentences = $text =~ /
    (
                                # sentences start with ...
        $opt_start_quote        # an optional start quote
        $opt_start_bracket      # an optional start bracket
        $capital_letter         # a capital letter ...
        .+?                     # at least some (non-greedy) anything ...
        $punctuation            # ... followed by any one of !?.
        $opt_close_quote        # an optional close quote
        $opt_close_bracket      # and an optional close bracket
    )
    (?=                         # with lookahead that it is followed by ...
        (?:                     # either ...
            \s+                 # some whitespace ...
            $opt_start_quote    # an optional start quote
            $opt_start_bracket  # an optional start bracket
            $capital_letter     # an uppercase word character (for locale
                                # sensitive matching)
        |               # or ...
            \n\n        # a couple (or more) of CRs
        |               # or ...
            \s*$        # optional whitespace, followed by end of string
        )
    )
    /gxs
    ;
    return @sentences if @sentences;
    return ( $text );
}

sub split_words{
    
    my $text = lc shift;
    my $re = qr/[\s \! \? \;\(\)\[\]\{\}\<\> " ]
 
# ... by COMMA, unless it has numbers on both sides: 3,000,000
|       (?<=\D) ,
|       , (?=\D)
 
# ... by FULL-STOP, SINGLE-QUOTE, HYPHEN, AMPERSAND, unless it has a letter on both sides
|       (?<=\W) [\.\-\&]
|       [\.\-\&] (?=\W)
 
# ... by QUOTE, unless it follows a letter (e.g. McDonald's, Holmes')
|       (?<=\W) [']
 
# ... by SLASH, if it has spaces on at least one side. (URLs shouldn't be split)
|       \s \/
|       \/ \s
 
# ... by COLON, unless it's a URL or a time (11:30am for e.g.)
|       \:(?!\/\/|\d)
/x;

    my @words=  split /$re/ , $text;
    $words[-1] =~ s/[\.\!\?]$//; # remove trailing puctuation at end of sentence.

    return @words if @words;
    return ( $text ); 
}


#NOTES:
# Online reference used :
# http://en.wikipedia.org/wiki/Sentence_boundary_disambiguation
# http://search.cpan.org/~tgrose/HTML-Summary-0.017/lib/Text/Sentence.pm (sentence regex)
# http://www.s-anand.net/blog/splitting-a-sentence-into-words/ (word regex)

# The code reads in each line, breaks it into sentences. It then
# processes each sentence breaking it into words. Each word, along
# with its frequency is then stored in the map. In the end, the map is sorted and printed out.

# The solution is not very scalable, and if building an acutal
# concordance I would use one of the available open-source libraries such as
# http://search.cpan.org/~emorgan/Lingua-Concordance-0.01/lib/Lingua/Concordance.pm
# and modify it as needed!

