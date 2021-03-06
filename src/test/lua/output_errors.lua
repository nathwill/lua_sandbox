-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.

require "cjson"
require "circular_buffer"; require "bloom_filter"; require "cuckoo_filter"
require "lpeg"
function process(tc)
    if tc == 0 then -- error internal reference
        output({})
    elseif tc == 1 then -- error escape overflow
        local escape = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
        for i=1, 10 do
            escape = escape .. escape
        end
        output(escape)
    elseif tc == 2 then -- unsupported userdata
        write_output(lpeg.P"")
    elseif tc == 3 then -- overflow
        local cb = circular_buffer.new(1000, 1, 60);
        write_output(cb)
    elseif tc == 4 then -- overflow cjson encode buffer
        local t = {}
        for i=1, 10 do
            t[#t+1] = "this is a test"
        end
        cjson.encode(t)
    end
    return 0
end
