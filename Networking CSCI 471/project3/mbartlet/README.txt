Michael Bartlett mbartlet 10603355

Note: There is about a 1/20 chance that the last test fails? For some reason the expected sequence # from B get's lost in context, and side A perpetually resends the packets in the window (none of which have the expected sequence). I ran the stresstest around 30 times in a row with success, and I couldn't coax out any error that should show me why this error occurs occasionally.

The way I do error detection is recalculate checksum and compare it to the packet's checksum (either the checksum or contents get corrupted). The types of corruption I can't detect is if the resulting checksum of a corrupted payload is identical to the packet's reported checksum. Otherwise I can detect corrupted payload, ack, and sequence number (sequence is passive, becuase if the sequence number is not the expected value in any case both sides pretend the packet was simply lost.)

No special compilation parameters, simple calle `make`.