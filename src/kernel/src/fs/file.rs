use super::driver;
use std::sync::Arc;

pub struct File {
    path: String,
    entry: Box<dyn driver::File<'static>>,

    // We need to hold this because "entry" is referencing it. So it should destroy after "entry"
    // that why we placed it here.
    #[allow(dead_code)]
    driver: Arc<dyn driver::Driver>,
}

impl File {
    pub(super) fn new(
        driver: Arc<dyn driver::Driver>,
        entry: Box<dyn driver::File<'static>>,
        path: String,
    ) -> Self {
        Self {
            driver,
            entry,
            path,
        }
    }

    pub fn path(&self) -> &str {
        self.path.as_ref()
    }
}