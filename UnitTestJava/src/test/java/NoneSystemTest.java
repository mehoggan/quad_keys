import com.quadkey.*;
import org.junit.BeforeClass;
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class NoneSystemTest {

    private boolean vectorContains(QuadKeyVector vect, QuadKey key) {
        boolean found = false;
        for (int i = 0; i < vect.size(); ++i) {
            QuadKey curr = vect.get(i);
            if (curr.equalTo(key)) {
                found = true;
                break;
            }
        }
        return found;
    }

    @BeforeClass
    public static void setUpBeforeClass() throws Exception {
        System.loadLibrary("QuadKey");
    }

    @Test
    public void isValidTest() {
        // See TestQuadKey TestSpecificCtorTest.
    }

    @Test
    public void isRootKeyTest() {
        // Same as BingSystem
    }

    @Test
    public void getParentTest() {
        // Same as BingSystem
    }

    @Test
    public void isMyAncestorTest() {
        // Same as BingSystem
    }

    @Test
    public void getAncestorTest() {
        // Same as BingSystem
    }

    @Test
    public void getChildTest() {
        // Same as BingSystem
    }

    @Test
    public void getChildrenTest() {
        // Same as BingSystem
    }

    @Test
    public void getDescendantsTest() {
        // Same as BingSystem
    }

    @Test
    public void getSiblingsTest() {
        // Same as BingSystem
    }

    @Test
    public void getNeighborsTest() {
        // Same as BingSystem
    }

    @Test
    public void fromStringToStringTest() {
    }

    @Test
    public void getGeoCoordinateBounds2dTest() {
    }

    @Test
    public void getKeyFromLongitudeLatitudeAtDepthToBoundsTest() {
    }

    @Test
    public void getKeysFromLongitudeLatitudeBoundingBoxTest() {
    }

    @Test
    public void selecetedCitiesTest() {
    }
}
