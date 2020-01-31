ardour {
	["type"]    = "session",
	name        = "Stop at Marker",
	license     = "MIT",
	author      = "Ardour Lua Task Force",
	description = [[An example session script which stops the transport on every location marker when rolling forward.]]
}

function factory ()
	return function (n_samples)
		if (not Session:transport_rolling ()) then
			-- not rolling, nothing to do.
			return
		end

		local pos = Session:transport_sample () -- current playhead position
		local loc = Session:locations () -- all marker locations

		-- find first marker after the current playhead position, ignore loop + punch ranges
		-- (this only works when rolling forward, to extend this example see
		-- http://manual.ardour.org/lua-scripting/class_reference/#ARDOUR:Locations )
		--
		local m = loc:first_mark_after (pos, false)

		if (m == -1) then
			-- no marker was found
			return
		end

		-- due to "first_mark_after" m is always > pos:
		-- assert(pos < m)
		-- so in the cycle that crosses "m" we need to stop at 'm'
		if (pos + n_samples >= m) then
			Session:request_locate (m, ARDOUR.LocateTransportDisposition.MustStop, ARDOUR.TransportRequestSource.TRS_Engine)
		end
	end
end
