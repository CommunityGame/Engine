--
-- Created by IntelliJ IDEA.
-- User: zion
-- Date: 08/07/15
-- Time: 11:32
--

objects = {};

G_delta = 0;

function update( delta )
	G_delta = G_delta + delta;
	for i = 1, table.getn( objects ) do
		objects[i]:setPos( 0, 2, 3 );
	end
end

function init()

	local root = GameObject( rootGameObject )

--	objects[1] = GameObject();

--	root:addObject( objects[1] );
end
