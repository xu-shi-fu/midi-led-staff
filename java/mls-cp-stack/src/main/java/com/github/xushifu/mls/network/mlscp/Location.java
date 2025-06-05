package com.github.xushifu.mls.network.mlscp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.github.xushifu.mls.utils.Strings;

public final class Location {

    public final static Location PING = create("/ping");
    public final static Location EXAMPLE = create("/example");

    public final static Location MODES = create("/modes");
    public final static Location MODES_CURRENT = create("/modes/current");
    public final static Location MODES_SUPPORT = create("/modes/support");

    public final static Location KEYS = create("/keys");
    public final static Location LEDS = create("/leds");
    public final static Location STYLES = create("/styles");

    private static void list_all(List<Location> dst) {
        dst.add(PING);
        dst.add(EXAMPLE);

        dst.add(MODES);
        dst.add(MODES_CURRENT);
        dst.add(MODES_SUPPORT);

        dst.add(LEDS);
        dst.add(STYLES);
        dst.add(KEYS);
    }

    private Location(String p) {
        this.path = p;
    }

    private final String path;

    private final static Table table = new Table();

    private static Location create(String path) {
        return new Location(path);
    }

    public static Location get(String text) {
        text = Strings.useEmpty(text);
        Location l = table.find(text);
        if (l == null) {
            l = create(text);
        }
        return l;
    }

    private static final class Table {

        final Map<String, Location> map;

        private Table() {
            this.map = new HashMap<>();
        }

        synchronized Location find(String str) {
            Map<String, Location> all = get_all();
            return all.get(str);
        }

        Map<String, Location> get_all() {
            Map<String, Location> all = map;
            if (all.isEmpty()) {
                load_all(all);
            }
            return all;
        }

        void load_all(Map<String, Location> dst) {
            List<Location> src = new ArrayList<>();
            list_all(src);
            for (Location l : src) {
                dst.put(l.path, l);
            }
        }
    }

    @Override
    public String toString() {
        return this.path;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((path == null) ? 0 : path.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Location other = (Location) obj;
        if (path == null) {
            if (other.path != null)
                return false;
        } else if (!path.equals(other.path))
            return false;
        return true;
    }
}
