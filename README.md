# mentorproj 1

    Description:
        This program allows you to find 3 winners from input files by searching maximum number of points

    Input formatting:

        Every row starting with '/' will be ignored ABSOLUTELY (you can use it like comment section). To become comment row needs to start with '/'.
        If row starts with '1/' of ' /' - it WONT be ignored

        First word of non-comment row is considered as name (every symbol before first ' ' is considered so)
        If you want to make space between first and second name - use '_' or '-' or '|' or whatever different from ' '

        Every information after name is considered as array of marks. Marks should be splitted by ' ' or ','
        (it actually can be splitted by any character, even by many characters like '44 ;;;\\ 99' - it will steal read 44 and 99)
        Each mark can be any POSITIVE integer (from 0 to 2^16), sign of negation is IGNORED.
        Float numbers are not allowed (multiple you float numbers to make them integers)

        Maximum input length is defined in LINE_SIZE and by default is 100. Increase it if you need to read MORE than 50 marks!

        Examples of formatting:

        /School competition 3

        Ivan_Gorev 9 10 10 10 9 9 10
        Isac_Arthur 10 10 10 10 10 10
        Kornev_Andrey 8 8 4 8 9 2
        Ionascu_Vladimir 9 7 4 6 2 1
         
