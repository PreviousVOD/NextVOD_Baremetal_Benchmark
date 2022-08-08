# The magic number below is the point where bootloader has completed initializing the LMI.

define box_setup
    sh4tp STMCLT2333_A:iptv7105:st40,no_pokes=1
    hbreak *0xA000008C
    continue
    delete breakpoint 1
        load

        hbreak _main
end

box_setup
