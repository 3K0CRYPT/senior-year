import javax.swing.table.DefaultTableModel;
import java.sql.*;
import java.util.Vector;

public class GuiModel extends DefaultTableModel {

    Connection db;
    Vector<Integer> albumIDs;   // will hold album ID values corresponding to search results
    int selectedRow;            // current selected row

    public GuiModel() {
        Object[] a = {"Artist", "Album Title", "Year"};
        setColumnIdentifiers(a);
    }

    public void setSelectedRow(int selectedRow) {
        this.selectedRow = selectedRow;
    }
    public void removeSelectedRow() {
        removeRow(selectedRow);
    }


    public int getAlbumID() {
        if (selectedRow != -1) {
            return albumIDs.elementAt(selectedRow);
        }
        else {
            return -1;
        }
    }

    public String getArtist() {
        if (selectedRow != -1) {
            return (String) getValueAt(selectedRow, 0);
        }
        else {
            return "";
        }
    }

    public String getAlbumTitle() {
        if (selectedRow != -1) {
            return (String) getValueAt(selectedRow, 1);
        }
        else {
            return "";
        }
    }

    public String getAlbumYear() {
        if (selectedRow != -1) {
            return (String) getValueAt(selectedRow, 2);
        }
        else {
            return "";
        }
    }

    public void login(String username, String password) throws SQLException, ClassNotFoundException {

        Class.forName("org.postgresql.Driver");
        String connectString = "jdbc:postgresql://flowers.mines.edu/csci403";

        db = DriverManager.getConnection(connectString, username, password);
        search("Artist", "");
    }

    public void search(String by, String val) throws SQLException {
        ResultSet rs;
        if (by.equals("Artist")) {
            rs = searchByArtist(val);
        }
        else if (by.equals("Album")) {
            rs = searchByAlbum(val);
        }
        else {
            throw new RuntimeException("Invalid search request");
        }
        if (rs == null) {
            setNumRows(1);
            setValueAt("Search by " + by + ":", 0, 0);
            setValueAt(val, 0, 1);
            setValueAt("(Not yet implemented)", 0, 2);
        }
        else {
            dataVector = new Vector<Vector<Object>>();
            albumIDs = new Vector<>();
            while (rs.next()) {
                Vector<Object> row = new Vector<>();
                row.add(rs.getString(1));
                row.add(rs.getString(2));
                row.add(rs.getString(3));
                dataVector.add(row);
                albumIDs.add(rs.getInt(4));
            }
            this.fireTableDataChanged();
        }
    }

    public ResultSet searchByArtist(String val) throws SQLException {

        // Note ResultSet *must* contain artist name, album title, album year, and album id,
        // in that order for the rest of the code to work properly!
        String query =
            "SELECT ar.name, al.title, al.year, al.id " +
            "FROM artist AS ar, album AS al " +
            "WHERE lower(ar.name) LIKE lower(?) " +
            "AND ar.id = al.artist_id " +
            "ORDER BY ar.name, al.year, al.title";

        PreparedStatement ps = db.prepareStatement(query);
        ps.setString(1, "%" + val + "%");
        return ps.executeQuery();
    }

    public ResultSet searchByAlbum(String val) throws SQLException {
    	String query =
                "SELECT ar.name, al.title, al.year, al.id " +
                "FROM artist AS ar, album AS al " +
                "WHERE lower(al.title) LIKE lower(?) " +
                "AND ar.id = al.artist_id " +
                "ORDER BY al.title, al.year, ar.name";

            PreparedStatement ps = db.prepareStatement(query);
            ps.setString(1, "%" + val + "%");
            return ps.executeQuery();
    }

    public Vector<String> getArtists() throws SQLException {
    	String query =
                "SELECT distinct(ar.name) " +
                "FROM artist AS ar " +
                "ORDER BY ar.name";   	
    	PreparedStatement ps = db.prepareStatement(query);        
        ResultSet rs = ps.executeQuery(); 
        Vector<String> list = new Vector<>();
        while (rs.next()) {
            list.add(rs.getString(1));            
        }
        return list;
    }

    public void insertArtist(String artist) throws SQLException {
    	String query = "INSERT INTO artist (name) VALUES (?)";                			  
    	PreparedStatement ps = db.prepareStatement(query);
        ps.setString(1, artist);
        ps.execute();
        System.out.println("Insert new artist: " + artist);        
    }

    public void insertAlbum(String artist, String title, String year) throws SQLException {
    	String query = "INSERT INTO album (artist_id, title, year) VALUES ((SELECT id FROM artist WHERE artist.name = ?), ?, CAST(? as numeric(4)))";                			  
    	PreparedStatement ps = db.prepareStatement(query);
        ps.setString(1, artist);
        ps.setString(2, title);
        if (year.isEmpty()) year = "0000";
        ps.setString(3, year);
        System.out.println(ps);
        ps.execute();        
        System.out.println("Insert new album: " + artist + " - " + title + "(" + year + ") ");
        search("Artist", "");        
    }

    public void updateAlbum(int albumID, String title, String year) throws SQLException {        
        System.out.println("Updating album id " + albumID + " to " + title + "(" + year + ")");
        setValueAt(title, selectedRow, 1);
        setValueAt(year, selectedRow, 2);
        String query = "UPDATE album al SET title=?, year = CAST(? as numeric(4)) WHERE al.id = CAST(? as numeric)";               			  
    	PreparedStatement ps = db.prepareStatement(query);
        ps.setString(1, title);
        ps.setString(2, year);
        ps.setString(3, Integer.toString(albumID));        
        ps.execute();        
        System.out.println("Insert new album: " + Integer.toString(albumID) + " - " + title + "(" + year + ") ");
        search("Artist", "");
    }

    public void deleteAlbum(int albumID) throws SQLException {
        System.out.println("Deleting album id: " + albumID);
        String query = "DELETE FROM album al WHERE al.id = CAST(? as numeric)";               			  
    	PreparedStatement ps = db.prepareStatement(query);
        ps.setString(1, Integer.toString(albumID));
        System.out.println(ps);
        ps.execute();        
        search("Artist", "");
    }
}
