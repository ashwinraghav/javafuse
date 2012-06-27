/*
 * JavaFuse - Java bindings for using FUSE.
 * Copyright (C) 2009 SRI International
 * 
 * This program is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free Software 
 * Foundation, either version 3 of the License, or (at your option) any later 
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with 
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Code taken from the FUSE-J project.
 */

import java.io.IOException;

public class DumpJVMLdPath
{
    public static void main(String[] args) throws IOException
    {
        String[] libDirs = System.getProperty("java.library.path", "").split(":");

        StringBuffer sb = new StringBuffer("");
        for (int i = 0; i < libDirs.length; i++)
            sb.append(" -L").append(libDirs[i]);

        System.out.println(sb.toString());
    }
}
